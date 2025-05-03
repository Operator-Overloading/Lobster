#include "Window.h"
#include "Logger.h"
#include "AppEvents.h"
#include "InputEvents.h"

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

		SetVSync(true);

		glfwSetWindowSizeCallback(_window,[](GLFWwindow* window,int width,int height)
		{
			Window& _window = *(Window*)glfwGetWindowUserPointer(window);
			_window.SetWidth(width);
			_window.SetWidth(width);

			WindowResizeEvent event(width,height);
			_window.event_callback(event);
		});

		glfwSetWindowMaximizeCallback(_window,[](GLFWwindow* window,int maximized)
		{
			Window& _window = *(Window*)glfwGetWindowUserPointer(window);

			if(maximized == 1)
			{
				_window.SetMinimized(false);
			}
			else
			{
				_window.SetMinimized(true);
			}
		});

		glfwSetWindowPosCallback(_window,[](GLFWwindow* window,int pos_x,int pos_y)
		{
			Window& _window = *(Window*)glfwGetWindowUserPointer(window);

			WindowMoveEvent event(pos_x,pos_y);
			_window.event_callback(event);
		});

		glfwSetWindowFocusCallback(_window,[](GLFWwindow* window,int focused)
		{
			Window& _window = *(Window*)glfwGetWindowUserPointer(window);

			if(focused == 1)
			{
				WindowFocusEvent event;
				_window.SetFocued(true);
				_window.event_callback(event);
			}
			else
			{
				WindowFocusLostEvent event;
				_window.SetFocued(false);
				_window.event_callback(event);
			}
		});

		glfwSetWindowCloseCallback(_window,[](GLFWwindow* window)
		{
			Window& _window = *(Window*)glfwGetWindowUserPointer(window);

			WindowCloseEvent event;
			_window.event_callback(event);
		});

		glfwSetKeyCallback(_window,[](GLFWwindow* window,int key,int scancode,int action,int mods)
		{
			Window& _window = *(Window*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key,false);
					_window.event_callback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					_window.event_callback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key,true);
					_window.event_callback(event);
					break;
				}
			}
		});

		glfwSetCharCallback(_window,[](GLFWwindow* window,unsigned int keycode)
		{
			Window& _window = *(Window*)glfwGetWindowUserPointer(window);

			KeyTypedEvent event(keycode);
			_window.event_callback(event);
		});

		glfwSetMouseButtonCallback(_window,[](GLFWwindow* window,int button,int action,int mods)
		{
			Window& _window = *(Window*)glfwGetWindowUserPointer(window);
			
			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseClickedEvent event(button);
					_window.event_callback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseReleasedEvent event(button);
					_window.event_callback(event);
					break;
				}
			}
		});

		glfwSetScrollCallback(_window,[](GLFWwindow* window,double offset_x,double offset_y)
		{
			Window& _window = *(Window*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)offset_x,(float)offset_y);
			_window.event_callback(event);
		});

		glfwSetCursorPosCallback(_window,[](GLFWwindow* window,double pos_x,double pos_y)
		{
			Window& _window = *(Window*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)pos_x,(float)pos_y);
			_window.event_callback(event);
		});
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

	void Window::SetVSync(bool vsync)
	{
		glfwSwapInterval(vsync);
		_vsync = vsync;
	}

#ifdef _WIN32
	HWND Window::GetWindowsHandle()
	{
		return glfwGetWin32Window(_window);
	}
#endif
}