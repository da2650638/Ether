#include "etherpch.h"

#include "RendererAPI.h"

namespace Ether
{
	//TODO: 应当根据平台相关的宏设置而不是像现在这样直接设置。
	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;
}