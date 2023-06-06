#include "etherpch.h"

#include "OpenGLShader.h"

#include <glad/glad.h>

namespace Ether
{
	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertex_shader_path, const std::string& fragment_shader_path)
		: m_RendererID(0),
		  m_Name(name)
	{
		ETHER_PROFILE_FUNCTION();

		std::string vertex_src = ReadShaderFile(vertex_shader_path);
		std::string fragment_src = ReadShaderFile(fragment_shader_path);
		CreateShader(vertex_src, fragment_src);
	}

	OpenGLShader::~OpenGLShader()
	{
		ETHER_PROFILE_FUNCTION();

		glDeleteProgram(m_RendererID);
	}

	std::string OpenGLShader::ReadShaderFile(const std::string& shader_file_path)
	{
		ETHER_PROFILE_FUNCTION();

		//TODO:搞明白seekg函数的语义。
		std::ifstream ifs(shader_file_path, std::ios::in, std::ios::binary);
		ETHER_CORE_ASSERT(ifs.is_open(), "Shader File:{0} open failed.", shader_file_path);
		ifs.seekg(0, std::ios::end);
		size_t shader_src_size = ifs.tellg();
		std::string shader_src(shader_src_size, '\0');
		ifs.seekg(0, std::ios::beg);
		ifs.read(&shader_src[0], shader_src_size);
		return shader_src;
	}

	void OpenGLShader::Bind() const
	{
		ETHER_PROFILE_FUNCTION();

		glUseProgram(m_RendererID);
	}

	void OpenGLShader::UnBind() const
	{
		ETHER_PROFILE_FUNCTION();

		glUseProgram(0);
	}

	const std::string& OpenGLShader::GetName() const
	{
		return m_Name;
	}

	void OpenGLShader::UploadUniformInt(const std::string& name, int value)
	{
		ETHER_PROFILE_FUNCTION();

		glUniform1i(glGetUniformLocation(m_RendererID, name.c_str()), value);
	}

	void OpenGLShader::UploadUniformIntArray(const std::string& name, int* value, uint32_t count)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1iv(location, count, value);
	}

	void OpenGLShader::UploadUniformFloat(const std::string& name, float value)
	{
		ETHER_PROFILE_FUNCTION();

		glUniform1f(glGetUniformLocation(m_RendererID, name.c_str()), value);
	}

	void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& value)
	{
		ETHER_PROFILE_FUNCTION();

		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2f(location, value.x, value.y);
	}

	void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& value)
	{
		ETHER_PROFILE_FUNCTION();

		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3f(location, value.x, value.y, value.z);
	}

	void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& value)
	{
		ETHER_PROFILE_FUNCTION();

		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& value)
	{
		ETHER_PROFILE_FUNCTION();

		glUniformMatrix3fv(glGetUniformLocation(m_RendererID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}

	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& value)
	{
		ETHER_PROFILE_FUNCTION();

		glUniformMatrix4fv(glGetUniformLocation(m_RendererID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}

	void OpenGLShader::CreateShader(const std::string& vertex_src, const std::string& fragment_src)
	{
		ETHER_PROFILE_FUNCTION();

		// Create an empty vertex shader handle
		GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
		// Send the vertex shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const GLchar* source = vertex_src.c_str();
		glShaderSource(vertex_shader, 1, &source, 0);
		// Compile the vertex shader
		glCompileShader(vertex_shader);
		GLint isCompiled = 0;
		glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &maxLength);
			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertex_shader, maxLength, &maxLength, &infoLog[0]);
			//we don't need the shader anymore if there are some errors.
			glDeleteShader(vertex_shader);
			ETHER_CORE_ERROR("{0}", infoLog.data());
			ETHER_CORE_ASSERT(false, "vertex shader failed to compile.");
			return;
		}
		// Create an empty fragment shader handle
		GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
		// Send the fragment shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		source = fragment_src.c_str();
		glShaderSource(fragment_shader, 1, &source, 0);
		// Compile the fragment shader
		glCompileShader(fragment_shader);
		glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragment_shader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(fragment_shader);
			// Either of them. Don't leak shaders.
			glDeleteShader(vertex_shader);

			ETHER_CORE_ERROR("{0}", infoLog.data());
			ETHER_CORE_ASSERT(false, "Fragment shader compilation failure!");
			return;
		}
		m_RendererID = glCreateProgram();
		glAttachShader(m_RendererID, vertex_shader);
		glAttachShader(m_RendererID, fragment_shader);
		glLinkProgram(m_RendererID);
		GLint isLinked = 0;
		glGetProgramiv(m_RendererID, GL_LINK_STATUS, (int*)&isLinked);
		glGetProgramiv(m_RendererID, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_RendererID, maxLength, &maxLength, &infoLog[0]);


			// We don't need the program anymore.
			glDeleteProgram(m_RendererID);
			// Don't leak shaders either.
			glDeleteShader(vertex_shader);
			glDeleteShader(fragment_shader);

			ETHER_CORE_ERROR("{0}", infoLog.data());
			ETHER_CORE_ASSERT(false, "Shader link failure!");
			return;
		}
		//Always detach shaders after a successful link.
		glDetachShader(m_RendererID, vertex_shader);
		glDetachShader(m_RendererID, fragment_shader);
		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);
	}
}