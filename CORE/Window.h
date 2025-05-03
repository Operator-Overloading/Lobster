#pragma once
#include <string>
#include <functional>

#ifdef _WIN32
#include <windows.h>
#endif

#include "Event.h"

struct GLFWwindow;

namespace Lobster
{
	class Window
	{
		using EventCallbackFn = std::function<void(Event&)>;
	public:
		Window(int width,int height,const std::string& title);
		~Window();

		void Update();
		bool ShouldClose() const;

		inline int GetWidth() const { return _width; }
		inline int GetHeight() const { return _height; }

		inline bool IsMinimized() const { return _minimized; }
		inline bool IsFocused() const { return _focused; }
		inline bool IsVSync() const { return _vsync; }

		inline void SetWidth(int width) { _width = width; }
		inline void SetHeight(int height) { _height = height; }

		inline void SetMinimized(bool minimized) { _minimized = minimized; }
		inline void SetFocued(bool focused) { _focused = focused; }

		void SetVSync(bool vsync);

		GLFWwindow* GetNativeWindow() const { return _window; }
#ifdef _WIN32
		HWND GetWindowsHandle();
#endif
		inline void SetEventCallback(const EventCallbackFn& func) { event_callback = func; }

		EventCallbackFn event_callback;
	private:
		GLFWwindow* _window;

		unsigned int _width,_height;
		std::string _title;

		bool _vsync = true,_minimized = false,_focused = true;
	};
}