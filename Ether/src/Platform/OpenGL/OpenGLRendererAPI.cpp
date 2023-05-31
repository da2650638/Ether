#include "etherpch.h"

#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace Ether
{
    void OpenGLDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
    {
        switch (severity)
        {
            case GL_DEBUG_SEVERITY_HIGH:         ETHER_CORE_CRITICAL(message); return;
            case GL_DEBUG_SEVERITY_MEDIUM:       ETHER_CORE_ERROR(message); return;
            case GL_DEBUG_SEVERITY_LOW:          ETHER_CORE_WARN(message); return;
            case GL_DEBUG_SEVERITY_NOTIFICATION: ETHER_CORE_TRACE(message); return;
        }

        ETHER_CORE_ASSERT(false, "Unknown severity level!");
    }

    OpenGLRendererAPI::OpenGLRendererAPI()
    {

    }

    OpenGLRendererAPI::~OpenGLRendererAPI()
    {

    }

    void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
    {
        glViewport(x, y, width, height);
    }

    void OpenGLRendererAPI::Init()
    {
        ETHER_PROFILE_FUNCTION();

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_DEPTH_TEST);
#ifdef ETH_DEBUG
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(OpenGLDebugCallback, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
#endif
    }

    void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void OpenGLRendererAPI::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertex_array)
    {
        glDrawElements(GL_TRIANGLES, vertex_array->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
    }
}