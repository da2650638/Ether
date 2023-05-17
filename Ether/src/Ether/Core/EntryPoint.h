#pragma once

#include "Ether/Core/Core.h"

int main(int argc, char** argv)
{
	Ether::Log::Init("Ether", "Sandbox");
	auto app = Ether::CreateApplication();
	app->Run();
	return 0;
}