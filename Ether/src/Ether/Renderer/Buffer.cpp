#include "etherpch.h"

#include "Buffer.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Ether
{
    VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::OpenGL:
                return new OpenGLVertexBuffer(vertices, size);
        }
        ETHER_CORE_ASSERT(false, "Unknow API type.");
        return nullptr;
    }
    IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
    {
        switch (RendererAPI::GetAPI())
        {
            case RendererAPI::API::OpenGL:
                return new OpenGLIndexBuffer(indices, size / sizeof(uint32_t) );
        }
        ETHER_CORE_ASSERT(false, "Unknow API type.");
        return nullptr;
    }
}