#pragma once

#include "Ether/Core/Core.h"

int main(int argc, char** argv)
{
	Ether::Log::Init("Ether", "Sandbox");

	ETHER_PROFILE_BEGIN_SESSION("StartUp", "Ether_StartUp.json");
	auto app = Ether::CreateApplication();
	ETHER_PROFILE_END_SESSION();

	ETHER_PROFILE_BEGIN_SESSION("Runtime", "Ether_Runtime.json");
	app->Run();
	ETHER_PROFILE_END_SESSION();
	
	ETHER_PROFILE_BEGIN_SESSION("Shutdown", "Ether_Shutdown.json");
	delete app;
	ETHER_PROFILE_END_SESSION();
	return 0;
}