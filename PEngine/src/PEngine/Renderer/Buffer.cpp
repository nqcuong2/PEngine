#include "pepch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "Platforms/OpenGL/OpenGLBuffer.h"

namespace PEngine
{
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
				PE_CORE_ASSERT(false, "RendererAPI::API::None is currently not supported!");
				return nullptr;

			case RendererAPI::API::OpenGL:
				return new OpenGLVertexBuffer(vertices, size);
		}

		PE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
				PE_CORE_ASSERT(false, "RendererAPI::API::None is currently not supported!");
				return nullptr;

			case RendererAPI::API::OpenGL:
				return new OpenGLIndexBuffer(indices, count);
		}

		PE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
	
}