#pragma once

#include "Ether.h"

#include "Image.h"

namespace Ether
{
	class RayTracerLayer : public Layer
	{
	public:
		RayTracerLayer(const std::string& name);

		virtual ~RayTracerLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate(Timestep ts) override;
		//�Ժ�Ҳ���ܼ�����ӱ�Ŀ�ܵĶ���
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event& e) override;
	private:
		Ref<Image> m_Image;
	};
}