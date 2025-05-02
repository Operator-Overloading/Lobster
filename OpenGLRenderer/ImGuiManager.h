#pragma once

struct GLFWwindow;

namespace Lobster
{
	class ImGuiManager
	{
	public:
		ImGuiManager(GLFWwindow* window);
		~ImGuiManager();

		void Init();
		void Shutdown();

		void BeginFrame();
		void EndFrame();

		void SetDisplaySize(int width,int height);
	private:
		GLFWwindow* _window;
	};
}