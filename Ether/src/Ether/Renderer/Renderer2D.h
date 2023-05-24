#pragma once

#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "OrthographicCamera.h"

#include "glm/glm.hpp"

namespace Ether
{
	class Renderer2D
	{
	public:
		static void Init();
		static void ShutDown();

		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		//Primitives
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture>& texture);
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture>& texture);
	};
}