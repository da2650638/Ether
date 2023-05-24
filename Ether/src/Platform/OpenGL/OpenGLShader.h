#pragma once

#include "Ether/Core/Core.h"
#include "Ether/Renderer/Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Ether
{
	class ETHER_API OpenGLShader : public Shader
	{
	public:
		OpenGLShader() = default;
		OpenGLShader(const std::string& name, const std::string& vertex_shader_path, const std::string& fragment_shader_path);
		virtual ~OpenGLShader();

		std::string ReadShaderFile(const std::string& shader_file_path);

		virtual void Bind() const override;
		virtual void UnBind() const override;
		virtual const std::string& GetName() const override;

		virtual void SetInt(const std::string& name, int value) override { UploadUniformInt(name, value); }

		virtual void SetFloat(const std::string& name, float value) override { UploadUniformFloat(name, value); }
		virtual void SetFloat2(const std::string& name, const glm::vec2& value) override { UploadUniformFloat2(name, value); }
		virtual void SetFloat3(const std::string& name, const glm::vec3& value) override { UploadUniformFloat3(name, value); }
		virtual void SetFloat4(const std::string& name, const glm::vec4& value) override { UploadUniformFloat4(name, value); }

		virtual void SetMat3(const std::string& name, const glm::mat3& matrix) override { UploadUniformMat3(name, matrix); }
		virtual void SetMat4(const std::string& name, const glm::mat4& matrix) override { UploadUniformMat4(name, matrix); }

		void UploadUniformInt(const std::string& name, int value);
		void UploadUniformFloat(const std::string& name, float value);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& value);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& value);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& value);
		void UploadUniformMat3(const std::string& name, const glm::mat3& value);
		void UploadUniformMat4(const std::string& name, const glm::mat4& value);
	private:
		void CreateShader(const std::string& vertex_src, const std::string& fragment_src);

	private:
		std::string m_Name;
		uint32_t m_RendererID;
	};
}