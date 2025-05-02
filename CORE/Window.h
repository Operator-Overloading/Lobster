#pragma once
#include <string>
#include <functional>

#ifdef _WIN32
#include <windows.h>
#endif

struct GLFWwindow;

namespace Lobster
{
	class Window
	{
	public:
		Window(int width,int height,const std::string& title);
		~Window();

		void Update();
		bool ShouldClose() const;

		int GetWidth() const { return _width; }
		int GetHeight() const { return _height; }
		GLFWwindow* GetNativeWindow() const { return _window; }
#ifdef _WIN32
		HWND GetWindowsHandle();
#endif

		void SetKeyCallback(std::function<void(int,int,int,int)> func);
		void SetMouseButtonCallback(std::function<void(int,int,int)> func);
		void SetCursorPosCallback(std::function<void(double,double)> func);
		void SetResizeCallback(std::function<void(int,int)> func);
	private:
		GLFWwindow* _window;
		unsigned int _width,_height;
		std::string _title;

		std::function<void(int,int,int,int)> _key_callback;
		std::function<void(int,int,int)> _mouse_button_callback;
		std::function<void(double,double)> _cursor_pos_callback;
		std::function<void(int,int)> _resize_callback;

		static void KeyCallbackWrapper(GLFWwindow* window,int key,int scancode,int action,int mods);
		static void MouseButtonCallbackWrapper(GLFWwindow* window,int button,int action,int mods);
		static void CursorPosCallbackWrapper(GLFWwindow* window,double xpos,double ypos);
		static void ResizeCallbackWrapper(GLFWwindow* window,int width,int height);
	};
}