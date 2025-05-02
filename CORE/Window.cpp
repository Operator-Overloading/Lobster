#include "Window.h"
#include "Logger.h"

#ifdef _WIN32
#define GLFW_EXPOSE_NATIVE_WIN32
#endif

#include <glfw/glfw3.h>
#include <glfw/glfw3native.h>

namespace Lobster
{
	Window::Window(int width,int height,const std::string& title) : _width(width),_height(height),_title(title)
	{
		if(!glfwInit())
			LOG_ERROR("Failed to initialize GLFW!");

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
		glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

		_window = glfwCreateWindow(_width,_height,_title.c_str(),0,0);

		if(!_window)
		{
			glfwTerminate();
			LOG_ERROR("Failed to create window!");
		}

		glfwMakeContextCurrent(_window);
		glfwSetWindowUserPointer(_window,this);
		glfwSetKeyCallback(_window,KeyCallbackWrapper);
		glfwSetMouseButtonCallback(_window,MouseButtonCallbackWrapper);
		glfwSetCursorPosCallback(_window,CursorPosCallbackWrapper);
		glfwSetWindowSizeCallback(_window,ResizeCallbackWrapper);

		glfwSwapInterval(1);
	}
	
	Window::~Window()
	{
		glfwDestroyWindow(_window);
		glfwTerminate();
	}

	void Window::Update()
	{
		glfwSwapBuffers(_window);
		glfwPollEvents();
	}

	bool Window::ShouldClose() const
	{
		return glfwWindowShouldClose(_window);
	}

#ifdef _WIN32
	HWND Window::GetWindowsHandle()
	{
		return glfwGetWin32Window(_window);
	}
#endif

	void Window::SetKeyCallback(std::function<void(int,int,int,int)> func)
	{
		_key_callback = func;
	}

	void Window::SetMouseButtonCallback(std::function<void(int,int,int)> func)
	{
		_mouse_button_callback = func;
	}

	void Window::SetCursorPosCallback(std::function<void(double,double)> func)
	{
		_cursor_pos_callback = func;
	}

	void Window::SetResizeCallback(std::function<void(int,int)> func)
	{
		_resize_callback = func;
	}

	void Window::KeyCallbackWrapper(GLFWwindow* window,int key,int scancode,int action,int mods)
	{
		Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
		if(win && win->_key_callback)
		{
			win->_key_callback(key,scancode,action,mods);
		}
	}

	void Window::MouseButtonCallbackWrapper(GLFWwindow* window,int button,int action,int mods)
	{
		Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
		if(win && win->_mouse_button_callback)
		{
			win->_mouse_button_callback(button,action,mods);
		}
	}

	void Window::CursorPosCallbackWrapper(GLFWwindow* window,double xpos,double ypos)
	{
		Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
		if(win && win->_cursor_pos_callback)
		{
			win->_cursor_pos_callback(xpos,ypos);
		}
	}

	void Window::ResizeCallbackWrapper(GLFWwindow* window,int width,int height)
	{
		Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
		if(win && win->_resize_callback)
		{
			win->_width = width;
			win->_height = height;
			win->_resize_callback(width,height);
		}
	}
}