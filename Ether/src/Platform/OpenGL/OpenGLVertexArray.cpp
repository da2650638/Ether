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
		//TODO: ��Ȼ�����VertexBuffer����ô��ǰvertex_buffer֮ǰ��VertexBuffer����ȥ�����ˣ�
		//��Ӽ���
		ETHER_CORE_ASSERT(vertex_buffer->GetLayout().GetElements().size(), "VertexBuffer has no layout!");
		//��VertexBuffer֮ǰһ��Ҫ��VertexArray
		glBindVertexArray(m_RendererID);
		vertex_buffer->Bind();

		//TODO: �˴���index��Ӧ�ú�vertex shader�е�uniform��Ŷ�Ӧ�ϵģ��ǲ���Ӧ�ý��ж�̬��Ӱ���
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
		//���ü���
		//��IndexBuffer֮ǰһ��Ҫ��VertexArray
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