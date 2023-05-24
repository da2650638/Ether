#pragma once

#include <string>

#include <glm/glm.hpp>

namespace Ether
{
	class Shader
	{
	public:
		Shader() = default;
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;
		virtual const std::string& GetName() const = 0;

		virtual void SetInt(const std::string& name, int value) = 0;

		virtual void SetFloat(const std::string& name, float value) = 0;
		virtual void SetFloat2(const std::string& name, const glm::vec2& value) = 0;
		virtual void SetFloat3(const std::string& name, const glm::vec3& value) = 0;
		virtual void SetFloat4(const std::string& name, const glm::vec4& value) = 0;

		virtual void SetMat3(const std::string& name, const glm::mat3& matrix) = 0;
		virtual void SetMat4(const std::string& name, const glm::mat4& matrix) = 0;

		static Ref<Shader> Create(const std::string& name, const std::string& vertex_shader_filepath, const std::string& fragment_shader_filepath);
	};

	class ShaderLibrary
	{
	public:
		ShaderLibrary() = default;
		~ShaderLibrary() = default;

		void Add(Ref<Shader> shader);
		void Add(const std::string& name, Ref<Shader> shader);
		Ref<Shader> Load(const std::string& name, const std::string& vertex_filepath, const std::string& fragment_filepath);

		Ref<Shader> Get(const std::string& name);
		bool Exist(const std::string& name);
		Ref<Shader> operator[](const std::string& name);

		std::unordered_map<std::string, Ref<Shader>>::iterator begin() { return m_Shaders.begin(); }
		std::unordered_map<std::string, Ref<Shader>>::iterator end() { return m_Shaders.end(); }
		std::unordered_map<std::string, Ref<Shader>>::const_iterator begin() const { return m_Shaders.begin(); }
		std::unordered_map<std::string, Ref<Shader>>::const_iterator end() const { return m_Shaders.end(); }
	private:
		std::unordered_map<std::string, Ref<Shader>> m_Shaders;
	};
}