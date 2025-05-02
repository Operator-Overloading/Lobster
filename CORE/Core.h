#pragma once
#include "Logger.h"
#include "MemoryManagment.h"
#include "Window.h"

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

		int Run();
	protected:
		bool is_running;
		Window window{960,800,"Lobsta"};
		std::unique_ptr<Renderer> renderer;
	};
}