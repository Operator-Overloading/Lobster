#pragma once
#include "Logger.h"
#include "MemoryManagment.h"
#include "Event.h"
#include "Window.h"
#include "Layer.h"

#include "OpenGLRenderer/Renderer.h"

namespace Lobster
{
	class LobsterCore
	{
	public:
		LobsterCore();
		~LobsterCore();

		virtual void OnStart() = 0;
		virtual void OnUpdate(float dt) = 0;

		void OnEvent(Event& event);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		int Run();
	protected:
		bool is_running;
		Window* window;
		std::unique_ptr<Renderer> renderer;
		LayerStack layer_stack;
	};
}