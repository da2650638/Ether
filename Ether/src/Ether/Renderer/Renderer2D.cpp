#include "etherpch.h"
#include "Renderer2D.h"
#include "RenderCommand.h"

#include "glm/gtc/matrix_transform.hpp"

namespace Ether
{
	struct QuadVertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoord;
	};

	struct Renderer2DData
	{
		const uint32_t MaxQuads = 10000;
		const uint32_t MaxVertices = MaxQuads * 4;
		const uint32_t MaxIndices = MaxQuads * 6;

		Ref<VertexArray> VertexArray;
		Ref<VertexBuffer> QuadVertexBuffer;
		Ref<ShaderLibrary> ShaderLibrary;
		Ref<Texture2D> WhiteTexture;

		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;
		uint32_t QuadIndexCount = 0;
	};

	struct Renderer2DStorage {
		Ref<VertexArray> VertexArray;
		Ref<ShaderLibrary> ShaderLibrary;
		Ref<Texture2D> WhiteTexture;
	};

	//static Renderer2DStorage* s_Data;
	static Renderer2DData s_Data;

	void Renderer2D::Init()
	{
		ETHER_PROFILE_FUNCTION();

		s_Data.ShaderLibrary.reset(new ShaderLibrary());

		//VertexBuffer and IndexBuffer
		s_Data.QuadVertexBuffer = VertexBuffer::Create(s_Data.MaxVertices * sizeof(QuadVertex));

		uint32_t offset = 0;
		//TODO: it's very dengerous, fix it in future
		uint32_t* indices = new uint32_t[s_Data.MaxIndices];
		for (int i = 0; i < s_Data.MaxIndices; i += 6)
		{
			indices[i    ] = offset + 0;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 2;

			indices[i + 3] = offset + 0;
			indices[i + 4] = offset + 2;
			indices[i + 5] = offset + 3;

			offset += 4;
		}
		Ref<IndexBuffer> index_buffer = IndexBuffer::Create(indices, s_Data.MaxIndices);
		delete[] indices;

		s_Data.QuadVertexBufferBase = new QuadVertex[s_Data.MaxQuads];
		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;

		BufferLayout layout = { {ShaderDataType::Float3, "a_Position"},{ShaderDataType::Float4, "a_Color"},{ShaderDataType::Float2, "a_TexCoord"} };
		s_Data.QuadVertexBuffer->SetLayout(layout);
		s_Data.VertexArray = VertexArray::Create();
		s_Data.VertexArray->AddVertexBuffer(s_Data.QuadVertexBuffer);
		s_Data.VertexArray->SetIndexBuffer(index_buffer);
		s_Data.ShaderLibrary->Load("Shader", "assets/shaders/Renderer2D/Vert.glsl", "assets/shaders/Renderer2D/Texture_Frag.glsl");
		s_Data.ShaderLibrary->Get("Shader")->Bind();
		s_Data.ShaderLibrary->Get("Shader")->SetInt("u_Texture", 0);
		s_Data.WhiteTexture = Texture2D::Create(1, 1);
		uint32_t white_texture_data = 0xffffffff;
		s_Data.WhiteTexture->SetData(&white_texture_data, sizeof(uint32_t));
	}

	void Renderer2D::ShutDown()
	{
		ETHER_PROFILE_FUNCTION();

		//TODO: fix this memory leak.
		//if (!s_Data)
		//{
		//	delete s_Data;
		//}
	}

	void Renderer2D::BeginScene(OrthographicCamera& camera)
	{
		ETHER_PROFILE_FUNCTION();

		for (auto iter : *(s_Data.ShaderLibrary))
		{
			auto shader = iter.second;
			shader->Bind();
			shader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
		}

		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;
		s_Data.QuadIndexCount = 0;
	}

	void Renderer2D::EndScene()
	{
		ETHER_PROFILE_FUNCTION();

		uint32_t data_size = (uint8_t*)s_Data.QuadVertexBufferPtr - (uint8_t*)s_Data.QuadVertexBufferBase;
		s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBufferBase, data_size);

		Flush();
	}

	void Renderer2D::Flush()
	{
		s_Data.ShaderLibrary->Get("Shader")->Bind();
		glm::mat4 transform = glm::mat4(1.0f);
		s_Data.ShaderLibrary->Get("Shader")->SetMat4("u_Transform", transform);
		s_Data.ShaderLibrary->Get("Shader")->SetFloat("u_TilingFactor", 1.0f);

		s_Data.VertexArray->Bind();
		s_Data.WhiteTexture->Bind(0);
		RenderCommand::DrawIndexed(s_Data.VertexArray, s_Data.QuadIndexCount);
		s_Data.WhiteTexture->UnBind(0);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		ETHER_PROFILE_FUNCTION();

		s_Data.QuadVertexBufferPtr->Position = { position.x, position.y, position.z };
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 0.0f };
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Position = { position.x + size.x, position.y, position.z };
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 0.0f };
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Position = { position.x + size.x, position.y + size.y, position.z };
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f };
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Position = { position.x, position.y + size.y, position.z };
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f };
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadIndexCount += 6;

		//TODO: rotation?
		/*
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Data.ShaderLibrary->Get("Shader")->Bind();
		s_Data.ShaderLibrary->Get("Shader")->SetMat4("u_Transform", transform);
		s_Data.ShaderLibrary->Get("Shader")->SetFloat4("u_Color", color);
		s_Data.ShaderLibrary->Get("Shader")->SetFloat("u_TilingFactor", 1.0f);

		s_Data.WhiteTexture->Bind(0);
		s_Data.VertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data.VertexArray);
		s_Data.WhiteTexture->UnBind(0);*/
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad(glm::vec3(position.x, position.y, 0.0f), size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		ETHER_PROFILE_FUNCTION();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Data.ShaderLibrary->Get("Shader")->Bind();
		s_Data.ShaderLibrary->Get("Shader")->SetMat4("u_Transform", transform);
		s_Data.ShaderLibrary->Get("Shader")->SetFloat4("u_Color", tintColor);
		s_Data.ShaderLibrary->Get("Shader")->SetFloat("u_TilingFactor", tilingFactor);

		texture->Bind(0);
		s_Data.VertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data.VertexArray);
		texture->UnBind(0);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		DrawQuad(glm::vec3(position.x, position.y, 0.0f), size, texture, tilingFactor, tintColor);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		DrawRotatedQuad(glm::vec3(position.x, position.y, 0.0f), size, rotation, color);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		ETHER_PROFILE_FUNCTION();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f }) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Data.ShaderLibrary->Get("Shader")->Bind();
		s_Data.ShaderLibrary->Get("Shader")->SetMat4("u_Transform", transform);
		s_Data.ShaderLibrary->Get("Shader")->SetFloat4("u_Color", color);
		s_Data.ShaderLibrary->Get("Shader")->SetFloat("u_TilingFactor", 1.0f);

		s_Data.WhiteTexture->Bind(0);
		s_Data.VertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data.VertexArray);
		s_Data.WhiteTexture->UnBind(0);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		DrawRotatedQuad(glm::vec3(position.x, position.y, 0.0f), size, rotation, texture, tilingFactor, tintColor);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		ETHER_PROFILE_FUNCTION();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f }) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Data.ShaderLibrary->Get("Shader")->Bind();
		s_Data.ShaderLibrary->Get("Shader")->SetMat4("u_Transform", transform);
		s_Data.ShaderLibrary->Get("Shader")->SetFloat4("u_Color", tintColor);
		s_Data.ShaderLibrary->Get("Shader")->SetFloat("u_TilingFactor", tilingFactor);

		texture->Bind(0);
		s_Data.VertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data.VertexArray);
		texture->UnBind(0);
	}
}