#include "Core.h"

#include <glfw/glfw3.h>
#include <imgui/imgui.h>

#include "InputEvents.h"
#include "AppEvents.h"

namespace Lobster
{
	LobsterCore::LobsterCore() : is_running(false)
	{
		window = new Window(960,800,"Lobsta");
		window->SetEventCallback(std::bind(&LobsterCore::OnEvent,this,std::placeholders::_1));
		renderer = std::make_unique<Renderer>(window->GetNativeWindow());
	}

	LobsterCore::~LobsterCore()
	{
	}

	void LobsterCore::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);

		for(auto it = layer_stack.rbegin(); it != layer_stack.rend(); ++it)
		{
			if(event.IsConsumed()) 
				break;

			(*it)->OnEvent(event);
		}
	}

	void LobsterCore::PushLayer(Layer* layer)
	{
		layer_stack.PushLayer(layer);
	}

	void LobsterCore::PushOverlay(Layer* overlay)
	{
		layer_stack.PushOverlay(overlay);
	}

	int LobsterCore::Run()
	{
		is_running = true;

#ifdef _DEBUG
		LoggerManager::AddLogger(std::make_shared<ConsoleLogger>());
#endif

		renderer->Init();
		renderer->SetViewport(0,0,window->GetWidth(),window->GetHeight());

		auto imgui_logger = std::make_shared<ImGuiConsoleLogger>();

		if(renderer->HasImGui())
		{
			LoggerManager::AddLogger(imgui_logger);
			LoggerManager::Attach();
		}

		OnStart();

		while(is_running)
		{
			window->Update();

			if(!window->IsMinimized())
			{
				renderer->Clear(0.12f,0.33f,0.33f,1.0f);

				renderer->BeginFrame();
				imgui_logger->Draw();

				OnUpdate(0.0f);

				{
					for(Layer* layer : layer_stack)
						layer->OnUpdate(0.0f);
				}

				renderer->EndFrame();
			}

			is_running = !window->ShouldClose();
		}

		return 0;
	}
}