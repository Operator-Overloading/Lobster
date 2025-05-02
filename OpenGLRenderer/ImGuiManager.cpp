#include "ImGuiManager.h"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include <glad/gl.h>
#include <glfw/glfw3.h>

namespace Lobster
{
	ImGuiManager::ImGuiManager(GLFWwindow* window) : _window(window)
	{
	}

	ImGuiManager::~ImGuiManager()
	{
		Shutdown();
	}

	void ImGuiManager::Init()
	{
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;

		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		ImGui::StyleColorsDark();

		ImGui_ImplGlfw_InitForOpenGL(_window,true);
		ImGui_ImplOpenGL3_Init("#version 330");
	}

	void ImGuiManager::Shutdown()
	{
		ImGui_ImplGlfw_Shutdown();
		ImGui_ImplOpenGL3_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiManager::BeginFrame()
	{
		ImGui_ImplGlfw_NewFrame();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiManager::EndFrame()
	{
		ImGuiIO& io = ImGui::GetIO(); (void)io;

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		ImGui::EndFrame();

		if(io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_window = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_window);
		}
	}

	void ImGuiManager::SetDisplaySize(int width,int height)
	{
		ImGuiIO& io = ImGui::GetIO(); (void)io;

		io.DisplaySize = ImVec2((float)width,(float)height);
	}
}