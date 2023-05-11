#include "etherpch.h"

#include "OpenGLVertexArray.h"
#include "OpenGLBuffer.h"

#include "glad/glad.h"

namespace Ether
{
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
		//TODO: 既然是添加VertexBuffer，那么当前vertex_buffer之前的VertexBuffer对象都去哪里了？
		//添加即绑定
		ETHER_CORE_ASSERT(vertex_buffer->GetLayout().GetElements().size(), "VertexBuffer has no layout!");
		//绑定VertexBuffer之前一定要绑定VertexArray
		glBindVertexArray(m_RendererID);
		vertex_buffer->Bind();

		//TODO: 此处的index是应该和vertex shader中的uniform编号对应上的，是不是应该进行动态添加啊？
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