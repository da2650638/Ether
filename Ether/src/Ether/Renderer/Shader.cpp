#include "etherpch.h"

#include "Renderer.h"
#include "Shader.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Ether
{
	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertex_shader_filepath, const std::string& fragment_shader_filepath)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::OpenGL:
				return std::make_shared<OpenGLShader>(name, vertex_shader_filepath, fragment_shader_filepath);
		}
		ETHER_CORE_ASSERT(false, "Unknow API type.");
		return nullptr;
	}

	void ShaderLibrary::Add(Ref<Shader> shader)
	{
		ETHER_CORE_ASSERT(!Exist(shader->GetName()), "shader {0} already exists in ShaderLibrary.", shader->GetName());
		m_Shaders[shader->GetName()] = shader;
	}

	void ShaderLibrary::Add(const std::string& name, Ref<Shader> shader)
	{
		ETHER_CORE_ASSERT(!Exist(name), "shader {0} already exists in ShaderLibrary.", name);
		m_Shaders[name] = shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& vertex_shader_filepath, const std::string& fragment_shader_filepath)
	{
		ETHER_CORE_ASSERT(!Exist(name), "shader {0} already exists in ShaderLibrary.", name);
		Ref<Shader> shader = Shader::Create(name, vertex_shader_filepath, fragment_shader_filepath);
		m_Shaders[name] = shader;
		return shader;
	}

	Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		ETHER_CORE_ASSERT(Exist(name), "shader {0} does not exist in ShaderLibrary.", name);
		return m_Shaders[name];
	}

	bool ShaderLibrary::Exist(const std::string& name)
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}
	Ref<Shader> ShaderLibrary::operator[](const std::string& name)
	{
		return Get(name);
	}
}