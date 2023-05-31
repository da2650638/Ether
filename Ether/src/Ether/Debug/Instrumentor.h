#pragma once

#include <string>
#include <chrono>
#include <algorithm>
#include <fstream>

#include <thread>

namespace Ether
{
	struct ProfileResult
	{
		std::string Name;
		long long Start;
		long long End;
		uint32_t ThreadID;
	};

	struct InstrumentationSession
	{
		std::string Name;
	};

	class Instrumentor
	{
	private:
		InstrumentationSession* m_CurrentSession;
		std::ofstream m_OutputStream;
		int m_ProfileCount;
	public:
		Instrumentor()
			: m_CurrentSession(nullptr), m_ProfileCount(0)
		{
		}

		void BeginSession(const std::string& name, const std::string& filepath = "results.json")
		{
			m_OutputStream.open(filepath);
			WriteHeader();
			m_CurrentSession = new InstrumentationSession{ name };
		}

		void EndSession()
		{
			WriteFooter();
			m_OutputStream.close();
			delete m_CurrentSession;
			m_CurrentSession = nullptr;
			m_ProfileCount = 0;
		}

		void WriteProfile(const ProfileResult& result)
		{
			if (m_ProfileCount++ > 0)
				m_OutputStream << ",\n";

			std::string name = result.Name;
			std::replace(name.begin(), name.end(), '"', '\'');

			m_OutputStream << "{\n";
			m_OutputStream << "\"cat\":\"function\",\n";
			m_OutputStream << "\"dur\":" << (result.End - result.Start) << ",\n";
			m_OutputStream << "\"name\":\"" << name << "\",\n";
			m_OutputStream << "\"ph\":\"X\",\n";
			m_OutputStream << "\"pid\":0,\n";
			m_OutputStream << "\"tid\":" << result.ThreadID << ",\n";
			m_OutputStream << "\"ts\":" << result.Start << "\n";
			m_OutputStream << "}";

			m_OutputStream.flush();
		}

		void WriteHeader()
		{
			m_OutputStream << "{\"otherData\": {},\n\"traceEvents\":[\n";
			m_OutputStream.flush();
		}

		void WriteFooter()
		{
			m_OutputStream << "]}\n";
			m_OutputStream.flush();
		}

		static Instrumentor& Get()
		{
			static Instrumentor instance;
			return instance;
		}
	};

	class InstrumentationTimer
	{
	public:
		InstrumentationTimer(const char* name)
			: m_Name(name), m_Stopped(false)
		{
			m_StartTimepoint = std::chrono::high_resolution_clock::now();
		}

		~InstrumentationTimer()
		{
			if (!m_Stopped)
				Stop();
		}

		void Stop()
		{
			auto endTimepoint = std::chrono::high_resolution_clock::now();
			long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
			long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

			uint32_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
			Instrumentor::Get().WriteProfile({ m_Name, start, end, threadID });
			m_Stopped = true;
		}
	private:
		const char* m_Name;
		std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
		bool m_Stopped;
	};
}



#define ETHER_PROFILE 0
#if ETHER_PROFILE
	// Resolve which function signature macro will be used. Note that this only
	// is resolved when the (pre)compiler starts, so the syntax highlighting
	// could mark the wrong one in your editor!
	#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
		#define ETHER_FUNC_SIG __PRETTY_FUNCTION__
	#elif defined(__DMC__) && (__DMC__ >= 0x810)
		#define ETHER_FUNC_SIG __PRETTY_FUNCTION__
	#elif defined(__FUNCSIG__)
		#define ETHER_FUNC_SIG __FUNCSIG__
	#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
		#define ETHER_FUNC_SIG __FUNCTION__
	#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
		#define ETHER_FUNC_SIG __FUNC__
	#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
		#define ETHER_FUNC_SIG __func__
	#elif defined(__cplusplus) && (__cplusplus >= 201103)
		#define ETHER_FUNC_SIG __func__
	#else
		#define ETHER_FUNC_SIG "ETHER_FUNC_SIG unknown!"
	#endif
	#define ETHER_PROFILE_BEGIN_SESSION(name, filepath) ::Ether::Instrumentor::Get().BeginSession(name, filepath)
	#define ETHER_PROFILE_END_SESSION() ::Ether::Instrumentor::Get().EndSession()
	#define ETHER_PROFILE_SCOPE(name) ::Ether::InstrumentationTimer timer##__LINE__(name)
	#define ETHER_PROFILE_FUNCTION() ETHER_PROFILE_SCOPE(ETHER_FUNC_SIG)
#else
	#define ETHER_PROFILE_BEGIN_SESSION(name, filepath) 
	#define ETHER_PROFILE_END_SESSION()
	#define ETHER_PROFILE_SCOPE(name)
	#define ETHER_PROFILE_FUNCTION()
#endif