#pragma once

#include "RendererAPI.h"
#include "RenderCommand.h"
#include "Shader.h"
#include "OrthographicCamera.h"

#include <glm/glm.hpp>

namespace Ether
{
	class Renderer
	{
	public:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static void Init();

		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void SetClearColor(const glm::vec4& color);
		static void Clear();

		static void OnWindowResize(uint32_t width, uint32_t height);
		static inline RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

		static void Submit(Ref<Shader> shader, Ref<VertexArray> vertex_array, glm::mat4 transform);
	private:
		static SceneData* m_SceneData;
		
	};
}