#include "etherpch.h"

#include "OpenGLVertexArray.h"

#include "glad/glad.h"

namespace Ether
{
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:  return GL_FLOAT;
			case ShaderDataType::Float2: return GL_FLOAT;
			case ShaderDataType::Float3: return GL_FLOAT;
			case ShaderDataType::Float4: return GL_FLOAT;
			case ShaderDataType::Mat3:   return GL_FLOAT;
			case ShaderDataType::Mat4:   return GL_FLOAT;
			case ShaderDataType::Int:    return GL_INT;
			case ShaderDataType::Int2:   return GL_INT;
			case ShaderDataType::Int3:   return GL_INT;
			case ShaderDataType::Int4:   return GL_INT;
			case ShaderDataType::Bool:   return GL_BOOL;
		}
		ETHER_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
		//glBindVertexArray(m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind()
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::UnBind()
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertex_buffer)
	{
		//添加即绑定
		ETHER_CORE_ASSERT(vertex_buffer->GetLayout().GetElements().size(), "VertexBuffer has no layout!");
		//绑定VertexBuffer之前一定要绑定VertexArray
		glBindVertexArray(m_RendererID);
		vertex_buffer->Bind();

		uint32_t index = 0;
		uint32_t stride = vertex_buffer->GetLayout().GetStride();
		for (const auto& element : vertex_buffer->GetLayout())
		{
			glVertexAttribPointer(
				0,
				element.GetElementCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				stride,
				(void*)element.Offset);
			glEnableVertexAttribArray(index);
			index++;
		}
		m_VertexBuffers.push_back(vertex_buffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& index_buffer)
	{
		//设置即绑定
		//绑定IndexBuffer之前一定要绑定VertexArray
		glBindVertexArray(m_RendererID);
		index_buffer->Bind();

		m_IndexBuffer = index_buffer;
	}

	const std::vector<Ref<VertexBuffer>>& OpenGLVertexArray::GetVertexBuffer() const
	{
		return m_VertexBuffers;
	}

	const Ref<IndexBuffer>& OpenGLVertexArray::GetIndexBuffer() const
	{
		return m_IndexBuffer;
	}
}