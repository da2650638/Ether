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
	private:
		std::unordered_map<std::string, Ref<Shader>> m_Shaders;
	};
}