#pragma once
#include "ImGuiManager.h"

struct GLFWwindow;

namespace Lobster
{
	class Renderer
	{
	public:
		Renderer(GLFWwindow* window);
		~Renderer();

		void Init();
		void Shutdown();

		void BeginFrame();
		void EndFrame();

		void Clear(float r,float g,float b,float a);

		void SetViewport(int x,int y,int width,int height);
	public:
		inline bool HasImGui() const { return _has_imgui; }
	private:
		GLFWwindow* _window;
		ImGuiManager* _imgui_manager;

		bool _has_imgui = false;
	};
}
