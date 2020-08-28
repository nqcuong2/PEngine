#pragma once

#include "RenderCommand.h"
#include "Camera.h"
#include "Shader.h"

namespace PEngine
{
	class Renderer
	{
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;

	public:
		static void Init();
		static void Shutdown();

		static void OnWindowResize(uint32_t width, uint32_t height);

		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1));

		static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};

}