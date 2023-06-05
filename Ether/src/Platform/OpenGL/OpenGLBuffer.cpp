#include "etherpch.h"

#include "OpenGLBuffer.h"

#include <glad/glad.h>

namespace Ether
{
	OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size)
	{
		ETHER_PROFILE_FUNCTION();
		glCreateBuffers(1, &m_RendererID);
		//创建即绑定
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
	{
		ETHER_PROFILE_FUNCTION();
		glCreateBuffers(1, &m_RendererID);
		//创建即绑定
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		//TODO: GL_STATIC_DRAW这个参数以后会不会由更改？
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		ETHER_PROFILE_FUNCTION();
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLVertexBuffer::Bind() const
	{
		ETHER_PROFILE_FUNCTION();
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLVertexBuffer::UnBind() const
	{
		ETHER_PROFILE_FUNCTION();
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenGLVertexBuffer::SetData(const void* data, uint32_t size)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}

	void OpenGLVertexBuffer::SetLayout(const BufferLayout& layout)
	{
		m_Layout = layout;
	}

	const BufferLayout& OpenGLVertexBuffer::GetLayout() const
	{
		return m_Layout;
	}

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)
		: m_Count(count)
	{
		ETHER_PROFILE_FUNCTION();
		glCreateBuffers(1, &m_RendererID);
		//创建即绑定
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		//TODO: GL_STATIC_DRAW这个参数以后会不会由更改？
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		ETHER_PROFILE_FUNCTION();
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLIndexBuffer::Bind() const
	{
		ETHER_PROFILE_FUNCTION();
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLIndexBuffer::UnBind() const
	{
		ETHER_PROFILE_FUNCTION();
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}

	uint32_t OpenGLIndexBuffer::GetCount() const
	{
		return m_Count;
	}
}