#include "Renderer.h"
#include "CORE/Logger.h"

#include <glad/gl.h>
#include <glfw/glfw3.h>

namespace Lobster
{
	Renderer::Renderer(GLFWwindow* window) : _window(window),_imgui_manager(new ImGuiManager(window)) {}

	Renderer::~Renderer()
	{
		Shutdown();
	}

	void Renderer::Init()
	{
		ASSERT(gladLoadGL(glfwGetProcAddress),"Failed to load GLAD!");

		glEnable(GL_DEPTH_TEST);

		LOG_INFO(reinterpret_cast<const char*>(glGetString(GL_VERSION)));
		LOG_INFO(reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
		LOG_INFO(reinterpret_cast<const char*>(glGetString(GL_RENDERER)));

#ifndef _NO_IMGUI
		_imgui_manager->Init();
		_has_imgui = true;
#endif
	}

	void Renderer::Shutdown()
	{
		_imgui_manager->Shutdown();
	}

	void Renderer::BeginFrame()
	{
		_imgui_manager->BeginFrame();
	}

	void Renderer::EndFrame()
	{
		_imgui_manager->EndFrame();
	}

	void Renderer::Clear(float r,float g,float b,float a)
	{
		glClearColor(r,g,b,a);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	}

	void Renderer::SetViewport(int x,int y,int width,int height)
	{
		glViewport(x,y,width,height);
		_imgui_manager->SetDisplaySize(width,height);
	}
}