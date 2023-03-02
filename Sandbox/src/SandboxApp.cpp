#include "Ether.h"

class Sandbox : public Ether::Application
{
public:
	Sandbox()
	{

	}

	virtual ~Sandbox()
	{

	}
};

Ether::Application* Ether::CreateApplication()
{
	return new Sandbox();
}