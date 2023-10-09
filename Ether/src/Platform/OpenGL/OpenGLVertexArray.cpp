#include "etherpch.h"

#include "OpenGLVertexArray.h"
#include "OpenGLBuffer.h"

#include "glad/glad.h"

namespace Ether
{
	OpenGLVertexArray::OpenGLVertexArray()
	{
		ETHER_PROFILE_FUNCTION();

		glCreateVertexArrays(1, &m_RendererID);
		//glBindVertexArray(m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		ETHER_PROFILE_FUNCTION();

		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind()
	{
		ETHER_PROFILE_FUNCTION();

		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::UnBind()
	{
		ETHER_PROFILE_FUNCTION();

		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertex_buffer)
	{
		ETHER_PROFILE_FUNCTION();

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
			//���ݲ�ͬ������д���
			switch (element.Type)
			{
				case ShaderDataType::Float:
				case ShaderDataType::Float2:
				case ShaderDataType::Float3:
				case ShaderDataType::Float4:
				{
					glEnableVertexAttribArray(index);
					glVertexAttribPointer(index,
										  element.GetElementCount(),
										  ShaderDataTypeToOpenGLBaseType(element.Type),
										  element.Normalized ? GL_TRUE : GL_FALSE,
										  stride,
										  (const void*)element.Offset);
					index++;
					break;
				}
				case ShaderDataType::Int:
				case ShaderDataType::Int2:
				case ShaderDataType::Int3:
				case ShaderDataType::Int4:
				case ShaderDataType::Bool:
				{
					glEnableVertexAttribArray(index);
					glVertexAttribIPointer(index,
										   element.GetElementCount(),
										   ShaderDataTypeToOpenGLBaseType(element.Type),
										   stride,
										   (const void*)element.Offset);
					index++;
					break;
				}
				case ShaderDataType::Mat3:
				case ShaderDataType::Mat4:
				{
					uint8_t count = element.GetElementCount();
					for (uint8_t i = 0; i < count; i++)
					{
						glEnableVertexAttribArray(index);
						glVertexAttribPointer(index,
							count,
							ShaderDataTypeToOpenGLBaseType(element.Type),
							element.Normalized ? GL_TRUE : GL_FALSE,
							stride,
							(const void*)(element.Offset + sizeof(float) * count * i));
						glVertexAttribDivisor(index, 1);
						index++;
					}
					break;
				}
				default:
					ETHER_CORE_ASSERT(false, "Unknown ShaderDataType!");
			}
		}

		m_VertexBuffers.push_back(vertex_buffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& index_buffer)
	{
		ETHER_PROFILE_FUNCTION();

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