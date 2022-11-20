#include "Ether.h"

class Sandbox : public Ether::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

Ether::Application* Ether::CreateApplication()
{
	return new Sandbox();
}