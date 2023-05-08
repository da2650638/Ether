#pragma once

#include "Ether/Renderer/Buffer.h"

#include <glad/glad.h>

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
		ETHER_CORE_ASSERT(false, "Unknown Shader Data Type.");
		return 0;
	}

	class ETHER_API OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual void SetLayout(const BufferLayout& layout) override;
		virtual const BufferLayout& GetLayout() const override;
	private:
		uint32_t m_RendererID;
		BufferLayout m_Layout;
	};

	class ETHER_API OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		//IndexBuffer�൱�еľ�̬����Create����ִ�й��캯��������Create�д��Ĳ������������ݵ���ʼ��ַ������Ĵ�С(�ֽ�)��
		//���������������ʼ��ַ��Ԫ�ص���������Create��������Ҫ����һ��ת����
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		~OpenGLIndexBuffer();

		virtual void Bind() const override;
		virtual void UnBind() const override;
		virtual uint32_t GetCount() const override;
	private:
		uint32_t m_RendererID;
		uint32_t m_Count;
	};
}