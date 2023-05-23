#pragma once
#include "Ether.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class Sandbox2D : public Ether::Layer {
public:
	Sandbox2D(const std::string& debugName);

	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(Ether::Timestep ts) override;
	//�Ժ�Ҳ���ܼ�����ӱ�Ŀ�ܵĶ���
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Ether::Event& e) override;
private:
	Ether::Ref<Ether::VertexArray> m_VertexArray;
	Ether::Ref<Ether::ShaderLibrary> m_ShaderLibrary;
	Ether::OrthographicCameraController m_OrthographicCameraController;

	glm::vec4 m_Color{ 0.2, 0.3, 0.8, 1.0 };
};