#pragma once

namespace Ether {

	class FileDialogs
	{
	public:
		// These return empty strings if cancelled
#ifdef ETH_PLATFORM_WINDOWS
		static std::optional<std::string> OpenFile(const char* filter);
		static std::optional<std::string> SaveFile(const char* filter);
#endif
	};

}