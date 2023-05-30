#include "etherpch.h"

#include "Renderer.h"
#include "Renderer2D.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Ether
{
	Renderer* Renderer::s_Instance = new Renderer();
	Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData();

	void Renderer::Init()
	{
		ETHER_PROFILE_FUNCTION();

		RenderCommand::Init();
		Renderer2D::Init();
	}

	void Renderer::ShutDown()
	{
		Renderer2D::ShutDown();
	}

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::SetClearColor(const glm::vec4& color)
	{
		RenderCommand::SetClearColor(color);
	}

	void Renderer::Clear()
	{
		RenderCommand::Clear();
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}

	void Renderer::Submit(Ref<Shader> shader, Ref<VertexArray> vertex_array, glm::mat4 transform)
	{
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);

		vertex_array->Bind();
		RenderCommand::DrawIndexed(vertex_array);
	}

	void* Renderer::Submit(RenderCommandFn fn, unsigned int size)
	{
		return s_Instance->m_CommandQueue.Allocate(fn, size);
	}

	void Renderer::WaitAndRender()
	{
		s_Instance->m_CommandQueue.Execute();
	}
}