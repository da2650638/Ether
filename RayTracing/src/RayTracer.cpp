#include "Ether.h"
#include "Ether/Core/EntryPoint.h"

#include "imgui.h"

#include "RayTracerLayer.h"

namespace Ether
{
	class RayTracer : public Application
	{
	public:
		RayTracer()
		{
			PushLayer(new RayTracerLayer("RayTracer"));
		}

		virtual ~RayTracer()
		{

		}
	};

	Application* CreateApplication()
	{
		return new RayTracer();
	}
}


