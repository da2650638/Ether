#pragma once

#include "Ether/Core.h"

int main(int argc, char** argv)
{
	Ether::Log::Init("Ether", "APP");
	auto app = Ether::CreateApplication();
	app->Run();
	return 0;
}