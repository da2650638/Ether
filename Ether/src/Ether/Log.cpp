#include "Log.h"

namespace Ether {
	Ref<spdlog::logger> Log::s_CoreLogger;
	Ref<spdlog::logger> Log::s_ClientLogger;

	void Log::Init(const std::string& coreName, const std::string& clientName)
	{
		spdlog::set_pattern("%^[%T]%n: %v%$");
		s_CoreLogger = spdlog::stdout_color_mt(coreName);
		s_ClientLogger = spdlog::stdout_color_mt(clientName);

		s_CoreLogger->set_level(spdlog::level::trace);
		s_ClientLogger->set_level(spdlog::level::trace);
	}
}