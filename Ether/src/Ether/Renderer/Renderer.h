#pragma once

#include "RendererAPI.h"
#include "RenderCommand.h"
#include "Shader.h"
#include "OrthographicCamera.h"
#include "RenderCommandQueue.h"

#include <glm/glm.hpp>

namespace Ether
{
	class Renderer
	{
	public:
		typedef void (*RenderCommandFn)(void*);

		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static void Init();
		static void ShutDown();

		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void SetClearColor(const glm::vec4& color);
		static void Clear();

		static void OnWindowResize(uint32_t width, uint32_t height);
		static inline RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

		static void Submit(Ref<Shader> shader, Ref<VertexArray> vertex_array, glm::mat4 transform);

		static void* Submit(RenderCommandFn fn, unsigned int size);

		void WaitAndRender();

		inline static Renderer* Get() { return s_Instance; }
	private:
		static SceneData* s_SceneData;
		static Renderer* s_Instance;
		
		RenderCommandQueue m_CommandQueue;
	};
}

#define ETHER_RENDER_PASTE(a, b) a ## b
#define ETHER_RENDER_PASTE2(a, b) ETHER_RENDER_PASTE(a, b)
#define ETHER_RENDER_UNIQUE(x) ETHER_RENDER_PASTE2(x, __LINE__)

#define ETHER_RENDER(code) \
	struct ETHER_RENDER_UNIQUE(EtherRenderCommand) {\
		static void Execute(void* argBuffer) \
		{\
			code;\
		}\
	};\
    void* ETHER_RENDER_UNIQUE(mem) = ::Ether::Renderer::Submit(ETHER_RENDER_UNIQUE(EtherRenderCommand)::Execute, sizeof(ETHER_RENDER_UNIQUE(EtherRenderCommand)));\
    ETHER_RENDER_UNIQUE(mem) = new (ETHER_RENDER_UNIQUE(mem)) ETHER_RENDER_UNIQUE(EtherRenderCommand)();

#define ETHER_RENDER_1(arg0, code) \
	struct ETHER_RENDER_UNIQUE(EtherRenderCommand) {\
		typedef std::remove_const<std::remove_reference<decltype(arg0)>::type>::type Arg0Type;\
		ETHER_RENDER_UNIQUE(EtherRenderCommand)(Arg0Type arg0) : arg0(arg0) {}\
		static void Execute(void* argBuffer)\
		{\
			Arg0Type arg0 = (*(ETHER_RENDER_UNIQUE(EtherRenderCommand)*)argBuffer).arg0;\
			code;\
		}\
		Arg0Type arg0;\
	};\
	void* ETHER_RENDER_UNIQUE(mem) = ::Ether::Renderer::Submit(ETHER_RENDER_UNIQUE(EtherRenderCommand)::Execute, sizeof(ETHER_RENDER_UNIQUE(EtherRenderCommand)));\
	ETHER_RENDER_UNIQUE(mem) = new (ETHER_RENDER_UNIQUE(mem)) ETHER_RENDER_UNIQUE(EtherRenderCommand)(arg0);

#define ETHER_RENDER_2(arg0, arg1, code) \
	struct ETHER_RENDER_UNIQUE(EtherRenderCommand) {\
		typedef std::remove_const<std::remove_reference<decltype(arg0)>::type>::type Arg0Type;\
		typedef std::remove_const<std::remove_reference<decltype(arg1)>::type>::type Arg1Type;\
		ETHER_RENDER_UNIQUE(EtherRenderCommand)(Arg0Type arg0,\
												Arg1Type arg1) : arg0(arg0), arg1(arg1) {}\
		static void Execute(void* argBuffer)\
		{\
			Arg0Type arg0 = (*(ETHER_RENDER_UNIQUE(EtherRenderCommand)*)argBuffer).arg0;\
			Arg1Type arg1 = (*(ETHER_RENDER_UNIQUE(EtherRenderCommand)*)argBuffer).arg1;\
			code;\
		}\
		Arg0Type arg0;\
		Arg1Type arg1;\
	};\
	void* ETHER_RENDER_UNIQUE(mem) = ::Ether::Renderer::Submit(ETHER_RENDER_UNIQUE(EtherRenderCommand)::Execute, sizeof(ETHER_RENDER_UNIQUE(EtherRenderCommand)));\
	ETHER_RENDER_UNIQUE(mem) = new (ETHER_RENDER_UNIQUE(mem)) ETHER_RENDER_UNIQUE(EtherRenderCommand)(arg0, arg1);

#define ETHER_RENDER_3(arg0, arg1, arg2, code) \
	struct ETHER_RENDER_UNIQUE(EtherRenderCommand) {\
		typedef std::remove_const<std::remove_reference<decltype(arg0)>::type>::type Arg0Type;\
		typedef std::remove_const<std::remove_reference<decltype(arg1)>::type>::type Arg1Type;\
		typedef std::remove_const<std::remove_reference<decltype(arg2)>::type>::type Arg2Type;\
		ETHER_RENDER_UNIQUE(EtherRenderCommand)(Arg0Type arg0,\
												Arg1Type arg1,\
												Arg2Type arg2) : arg0(arg0), arg1(arg1), arg2(arg2) {}\
		static void Execute(void* argBuffer)\
		{\
			Arg0Type arg0 = (*(ETHER_RENDER_UNIQUE(EtherRenderCommand)*)argBuffer).arg0;\
			Arg1Type arg1 = (*(ETHER_RENDER_UNIQUE(EtherRenderCommand)*)argBuffer).arg1;\
			Arg2Type arg2 = (*(ETHER_RENDER_UNIQUE(EtherRenderCommand)*)argBuffer).arg2;\
			code;\
		}\
		Arg0Type arg0;\
		Arg1Type arg1;\
		Arg2Type arg2;\
	};\
	void* ETHER_RENDER_UNIQUE(mem) = ::Ether::Renderer::Submit(ETHER_RENDER_UNIQUE(EtherRenderCommand)::Execute, sizeof(ETHER_RENDER_UNIQUE(EtherRenderCommand)));\
	ETHER_RENDER_UNIQUE(mem) = new (ETHER_RENDER_UNIQUE(mem)) ETHER_RENDER_UNIQUE(EtherRenderCommand)(arg0, arg1, arg2);

#define ETHER_RENDER_4(arg0, arg1, arg2, arg3, code) \
	struct ETHER_RENDER_UNIQUE(EtherRenderCommand) {\
		typedef std::remove_const<std::remove_reference<decltype(arg0)>::type>::type Arg0Type;\
		typedef std::remove_const<std::remove_reference<decltype(arg1)>::type>::type Arg1Type;\
		typedef std::remove_const<std::remove_reference<decltype(arg2)>::type>::type Arg2Type;\
		typedef std::remove_const<std::remove_reference<decltype(arg3)>::type>::type Arg3Type;\
		ETHER_RENDER_UNIQUE(EtherRenderCommand)(Arg0Type arg0,\
												Arg1Type arg1,\
												Arg2Type arg2,\
												Arg3Type arg3) : arg0(arg0), arg1(arg1), arg2(arg2), arg3(arg3) {}\
		static void Execute(void* argBuffer)\
		{\
			Arg0Type arg0 = (*(ETHER_RENDER_UNIQUE(EtherRenderCommand)*)argBuffer).arg0;\
			Arg1Type arg1 = (*(ETHER_RENDER_UNIQUE(EtherRenderCommand)*)argBuffer).arg1;\
			Arg2Type arg2 = (*(ETHER_RENDER_UNIQUE(EtherRenderCommand)*)argBuffer).arg2;\
			Arg3Type arg3 = (*(ETHER_RENDER_UNIQUE(EtherRenderCommand)*)argBuffer).arg3;\
			code;\
		}\
		Arg0Type arg0;\
		Arg1Type arg1;\
		Arg2Type arg2;\
		Arg3Type arg3;\
	};\
	void* ETHER_RENDER_UNIQUE(mem) = ::Ether::Renderer::Submit(ETHER_RENDER_UNIQUE(EtherRenderCommand)::Execute, sizeof(ETHER_RENDER_UNIQUE(EtherRenderCommand)));\
	ETHER_RENDER_UNIQUE(mem) = new (ETHER_RENDER_UNIQUE(mem)) ETHER_RENDER_UNIQUE(EtherRenderCommand)(arg0, arg1, arg2, arg3);

#define ETHER_RENDER_S(code) auto self = this;\
	ETHER_RENDER_1(self, code)

#define ETHER_RENDER_S1(arg0, code) auto self = this;\
	ETHER_RENDER_2(self, arg0, code)

#define ETHER_RENDER_S2(arg0, arg1, code) auto self = this;\
	ETHER_RENDER_3(self, arg0, arg1, code)

#define ETHER_RENDER_S3(arg0, arg1, arg2, code) auto self = this;\
	ETHER_RENDER_4(self, arg0, arg1, arg2, code)