#include "etherpch.h"
#include "Renderer2D.h"
#include "RenderCommand.h"

#include "glm/gtc/matrix_transform.hpp"

namespace Ether
{
	struct Renderer2DStorage {
		Ref<VertexArray> VertexArray;
		Ref<ShaderLibrary> ShaderLibrary;
		Ref<Texture2D> WhiteTexture;
	};

	static Renderer2DStorage* s_Data;

	void Renderer2D::Init()
	{
		ETHER_PROFILE_FUNCTION();

		s_Data = new Renderer2DStorage;
		s_Data->ShaderLibrary.reset(new ShaderLibrary());
		float vertices[] = {
			0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
			0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
			-0.5f, 0.5f,  0.0f, 0.0f, 1.0f,
			-0.5, -0.5f,  0.0f, 0.0f, 0.0f
		};
		uint32_t indices[] = {
			0, 1, 2,
			1, 2, 3
		};
		Ref<VertexBuffer> vertex_buffer = VertexBuffer::Create(vertices, sizeof(vertices));
		Ref<IndexBuffer> index_buffer = IndexBuffer::Create(indices, sizeof(indices));
		BufferLayout layout = { {ShaderDataType::Float3, "a_Position"}, {ShaderDataType::Float2, "a_TexCoord"} };
		vertex_buffer->SetLayout(layout);
		s_Data->VertexArray = VertexArray::Create();
		s_Data->VertexArray->AddVertexBuffer(vertex_buffer);
		s_Data->VertexArray->SetIndexBuffer(index_buffer);
		s_Data->ShaderLibrary->Load("Shader", "assets/shaders/Renderer2D/Vert.glsl", "assets/shaders/Renderer2D/Texture_Frag.glsl");
		s_Data->ShaderLibrary->Get("Shader")->Bind();
		s_Data->ShaderLibrary->Get("Shader")->SetInt("u_Texture", 0);
		s_Data->WhiteTexture = Texture2D::Create(1, 1);
		uint32_t white_texture_data = 0xffffffff;
		s_Data->WhiteTexture->SetData(&white_texture_data, sizeof(uint32_t));
	}

	void Renderer2D::ShutDown()
	{
		ETHER_PROFILE_FUNCTION();

		//TODO: fix this memory leak.
		if (!s_Data)
		{
			delete s_Data;
		}
	}

	void Renderer2D::BeginScene(OrthographicCamera& camera)
	{
		ETHER_PROFILE_FUNCTION();

		for (auto iter : *(s_Data->ShaderLibrary))
		{
			auto shader = iter.second;
			shader->Bind();
			shader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
		}
	}

	void Renderer2D::EndScene()
	{
		ETHER_PROFILE_FUNCTION();
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		ETHER_PROFILE_FUNCTION();

		//TODO: rotation?
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Data->ShaderLibrary->Get("Shader")->Bind();
		s_Data->ShaderLibrary->Get("Shader")->SetMat4("u_Transform", transform);
		s_Data->ShaderLibrary->Get("Shader")->SetFloat4("u_Color", color);

		s_Data->WhiteTexture->Bind(0);
		s_Data->VertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->VertexArray);
		s_Data->WhiteTexture->UnBind(0);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad(glm::vec3(position.x, position.y, 1.0f), size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture>& texture)
	{
		ETHER_PROFILE_FUNCTION();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Data->ShaderLibrary->Get("Shader")->Bind();
		s_Data->ShaderLibrary->Get("Shader")->SetMat4("u_Transform", transform);
		s_Data->ShaderLibrary->Get("Shader")->SetFloat4("u_Color", glm::vec4(1.0f));

		texture->Bind(0);
		s_Data->VertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->VertexArray);
		texture->UnBind(0);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture>& texture)
	{
		DrawQuad(glm::vec3(position.x, position.y, 1.0f), size, texture);
	}
}