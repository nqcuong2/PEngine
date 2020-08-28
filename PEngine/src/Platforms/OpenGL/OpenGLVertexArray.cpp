#include "pepch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace PEngine
{
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case PEngine::ShaderDataType::None:		return GL_FLOAT;
			case PEngine::ShaderDataType::Float:	return GL_FLOAT;
			case PEngine::ShaderDataType::Float2:	return GL_FLOAT;
			case PEngine::ShaderDataType::Float3:	return GL_FLOAT;
			case PEngine::ShaderDataType::Float4:	return GL_FLOAT;
			case PEngine::ShaderDataType::Mat3:		return GL_FLOAT;
			case PEngine::ShaderDataType::Mat4:		return GL_FLOAT;
			case PEngine::ShaderDataType::Int:		return GL_INT;
			case PEngine::ShaderDataType::Int2:		return GL_INT;
			case PEngine::ShaderDataType::Int3:		return GL_INT;
			case PEngine::ShaderDataType::Int4:		return GL_INT;
			case PEngine::ShaderDataType::Bool:		return GL_BOOL;
		}

		PE_CORE_ASSERT(false, "Unknown ShaderDataType");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		PE_PROFILE_FUNCTION();

		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		PE_PROFILE_FUNCTION();

		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		PE_PROFILE_FUNCTION();

		glBindVertexArray(m_RendererID);
	}
	void OpenGLVertexArray::Unbind() const
	{
		PE_PROFILE_FUNCTION();

		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		PE_PROFILE_FUNCTION();

		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		PE_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset);
			++index;
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		PE_PROFILE_FUNCTION();

		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}
}