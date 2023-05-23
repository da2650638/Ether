#pragma once
#include "Ether.h"

class Sandbox2D : public Ether::Layer {
public:
	Sandbox2D(const std::string& debugName);

	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(Ether::Timestep ts) override;
	//以后也可能继续添加别的框架的东西
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Ether::Event& e) override;
private:
	Ether::Ref<Ether::VertexArray> m_VertexArray;
	Ether::Ref<Ether::ShaderLibrary> m_ShaderLibrary;
	Ether::OrthographicCameraController m_OrthographicCameraController;
};