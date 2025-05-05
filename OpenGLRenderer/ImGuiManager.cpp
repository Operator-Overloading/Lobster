#include "ImGuiManager.h"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include <glad/gl.h>
#include <glfw/glfw3.h>

#include "CORE/Logger.h"

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
		ImGuiStyle& style = ImGui::GetStyle();

		io.Fonts->Clear();

		ImFontConfig font_config;
		font_config.MergeMode = false;
		font_config.GlyphMinAdvanceX = 4.0f;
		font_config.GlyphMaxAdvanceX = 13.0f;

		ImFont* font_commissioner = io.Fonts->AddFontFromFileTTF("../Fonts/commissioner.ttf",16.0f,&font_config,io.Fonts->GetGlyphRangesDefault());
		ImFont* font_outfit = io.Fonts->AddFontFromFileTTF("../Fonts/outfit.ttf",16.0f,&font_config,io.Fonts->GetGlyphRangesDefault());

		io.Fonts->Build();

		io.FontDefault = font_commissioner;

		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		style.Alpha = 1.0f;
		style.AntiAliasedFill = true;
		style.AntiAliasedLines = true;
		style.AntiAliasedLinesUseTex = true;
		style.ButtonTextAlign = ImVec2(0.5f,0.5f);
		style.CellPadding = ImVec2(0.0f,0.0f);
		style.ChildBorderSize = 1.0f;
		style.ChildRounding = 0.1f;
		style.CircleTessellationMaxError = 0.5f;
		style.ColorButtonPosition = ImGuiDir::ImGuiDir_Right;

		style.Alpha = 1.0f;
        style.FrameRounding = 0.8f;

        ImVec4 col_text = ImVec4(1.0f,1.0f,1.0f,1.0f);
		ImVec4 col_main = ImVec4(0.2f,0.2f,0.2f,1.0f);
		ImVec4 col_back = ImVec4(0.14f,0.14f,0.14f,1.0f);
		ImVec4 col_area = ImVec4(0.17f,0.17f,0.17f,1.0f);

		style.Colors[ImGuiCol_Text]                  = ImVec4(col_text.x, col_text.y, col_text.z, 1.00f);
		style.Colors[ImGuiCol_TextDisabled]          = ImVec4(col_text.x, col_text.y, col_text.z, 0.58f);
		style.Colors[ImGuiCol_WindowBg]              = ImVec4(col_back.x, col_back.y, col_back.z, 1.00f);
		style.Colors[ImGuiCol_ChildBg]               = ImVec4(col_area.x, col_area.y, col_area.z, 0.00f);
		style.Colors[ImGuiCol_Border]                = ImVec4(col_text.x, col_text.y, col_text.z, 0.30f);
		style.Colors[ImGuiCol_BorderShadow]          = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		style.Colors[ImGuiCol_FrameBg]               = ImVec4(col_area.x, col_area.y, col_area.z, 1.00f);
		style.Colors[ImGuiCol_FrameBgHovered]        = ImVec4(col_main.x, col_main.y, col_main.z, 0.68f);
		style.Colors[ImGuiCol_FrameBgActive]         = ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
		style.Colors[ImGuiCol_TitleBg]               = ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
		style.Colors[ImGuiCol_TitleBgCollapsed]      = ImVec4(col_main.x, col_main.y, col_main.z, 0.50f);
		style.Colors[ImGuiCol_TitleBgActive]         = ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
		style.Colors[ImGuiCol_MenuBarBg]             = ImVec4(col_area.x, col_area.y, col_area.z, 0.57f);
		style.Colors[ImGuiCol_ScrollbarBg]           = ImVec4(col_area.x, col_area.y, col_area.z, 1.00f);
		style.Colors[ImGuiCol_ScrollbarGrab]         = ImVec4(col_main.x, col_main.y, col_main.z, 0.31f);
		style.Colors[ImGuiCol_ScrollbarGrabHovered]  = ImVec4(col_main.x, col_main.y, col_main.z, 0.78f);
		style.Colors[ImGuiCol_ScrollbarGrabActive]   = ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
		style.Colors[ImGuiCol_CheckMark]             = ImVec4(      1.0f,       1.0f,       1.0f, 1.00f);
		style.Colors[ImGuiCol_SliderGrab]            = ImVec4(col_main.x, col_main.y, col_main.z, 0.24f);
		style.Colors[ImGuiCol_SliderGrabActive]      = ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
		style.Colors[ImGuiCol_Button]                = ImVec4(col_main.x, col_main.y, col_main.z, 0.44f);
		style.Colors[ImGuiCol_ButtonHovered]         = ImVec4(col_main.x, col_main.y, col_main.z, 0.86f);
		style.Colors[ImGuiCol_ButtonActive]          = ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
		style.Colors[ImGuiCol_Header]                = ImVec4(col_main.x, col_main.y, col_main.z, 0.76f);
		style.Colors[ImGuiCol_HeaderHovered]         = ImVec4(col_main.x, col_main.y, col_main.z, 0.86f);
		style.Colors[ImGuiCol_HeaderActive]          = ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
		style.Colors[ImGuiCol_ResizeGrip]            = ImVec4(col_main.x, col_main.y, col_main.z, 0.20f);
		style.Colors[ImGuiCol_ResizeGripHovered]     = ImVec4(col_main.x, col_main.y, col_main.z, 0.78f);
		style.Colors[ImGuiCol_ResizeGripActive]      = ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
		style.Colors[ImGuiCol_PlotLines]             = ImVec4(col_text.x, col_text.y, col_text.z, 0.63f);
		style.Colors[ImGuiCol_PlotLinesHovered]      = ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
		style.Colors[ImGuiCol_PlotHistogram]         = ImVec4(col_text.x, col_text.y, col_text.z, 0.63f);
		style.Colors[ImGuiCol_PlotHistogramHovered]  = ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
		style.Colors[ImGuiCol_TextSelectedBg]        = ImVec4(col_main.x, col_main.y, col_main.z, 0.43f);
		style.Colors[ImGuiCol_DockingPreview]        = ImVec4(     0.11f,      0.33f,      0.66f, 1.00f);
		style.Colors[ImGuiCol_DockingEmptyBg]        = ImVec4(     0.11f,      0.36f,      0.48f, 1.00f);
		style.Colors[ImGuiCol_Separator]             = ImVec4(     0.11f,      0.41f,      0.72f, 1.00f);
		style.Colors[ImGuiCol_SeparatorActive]       = ImVec4(     0.11f,      0.41f,      0.72f, 0.83f);
		style.Colors[ImGuiCol_SeparatorHovered]      = ImVec4(     0.11f,      0.41f,      0.72f, 0.64f);

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