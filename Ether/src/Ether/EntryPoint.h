#pragma once

#include "Ether/Core.h"

int main(int argc, char** argv)
{
	auto app = Ether::CreateApplication();
	app->Run();
	return 0;
}