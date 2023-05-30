#include "etherpch.h"

#include "RenderCommandQueue.h"

namespace Ether
{
	RenderCommandQueue::RenderCommandQueue()
		: m_CommandCount(0)
	{
		m_CommandBuffer = new unsigned char[16 * 1024 * 1024];
		m_CommandBufferPtr = m_CommandBuffer;
		memset(m_CommandBuffer, 0, static_cast<size_t>(16 * 1024 * 1024));
	}

	RenderCommandQueue::~RenderCommandQueue()
	{
		delete[] m_CommandBuffer;
	}

	void* RenderCommandQueue::Allocate(RenderCommandFn fn, unsigned int size)
	{
		*(RenderCommandFn*)m_CommandBufferPtr = fn;
		m_CommandBufferPtr += sizeof(RenderCommandFn);

		*(unsigned int*)m_CommandBufferPtr = size;
		m_CommandBufferPtr += sizeof(unsigned int);

		void* memory = m_CommandBufferPtr;
		m_CommandBufferPtr += size;

		m_CommandCount++;
		return memory;
	}

	void RenderCommandQueue::Execute()
	{
		ETHER_CORE_TRACE("RenderCommandQueue::Execute -- {0} commands, {1} bytes", m_CommandCount, (m_CommandBufferPtr - m_CommandBuffer));

		unsigned char* buffer = m_CommandBuffer;
		for (int i = 0; i < m_CommandCount; i++)
		{
			RenderCommandFn function = *(RenderCommandFn*)buffer;
			buffer += sizeof(RenderCommandFn);

			unsigned int size = *(unsigned int*)buffer;
			buffer += sizeof(unsigned int);

			function(buffer);
			buffer += size;
		}

		m_CommandBufferPtr = m_CommandBuffer;
		m_CommandCount = 0;
	}
}