#pragma once

#include "Core.h"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/fmt/ostr.h>

namespace Ether {

	class ETHER_API Log {
	public:
		Log() = delete;
		~Log() = delete;

		static void Init(const std::string& corename, const std::string& clientname);

		inline static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClientLogger;
	};

}

#define ETHER_CORE_CRITICAL(...) Ether::Log::GetCoreLogger()->critical(__VA_ARGS__)
#define ETHER_CORE_ERROR(...)    Ether::Log::GetCoreLogger()->error(__VA_ARGS__)
#define ETHER_CORE_WARN(...)     Ether::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ETHER_CORE_INFO(...)     Ether::Log::GetCoreLogger()->info(__VA_ARGS__)
#define ETHER_CORE_TRACE(...)    Ether::Log::GetCoreLogger()->trace(__VA_ARGS__)

#define ETHER_CRITICAL(...)      Ether::Log::GetClientLogger()->critical(__VA_ARGS__)
#define ETHER_ERROR(...)         Ether::Log::GetClientLogger()->error(__VA_ARGS__)
#define ETHER_WARN(...)          Ether::Log::GetClientLogger()->warn(__VA_ARGS__)
#define ETHER_INFO(...)          Ether::Log::GetClientLogger()->info(__VA_ARGS__)
#define ETHER_TRACE(...)         Ether::Log::GetClientLogger()->trace(__VA_ARGS__)