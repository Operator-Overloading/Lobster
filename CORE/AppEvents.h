#pragma once
#include "Event.h"

#include <sstream>

namespace Lobster
{
	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width,unsigned int height) : _width(width),_height(height) {}

		unsigned int GetWidth() const { return _width; }
		unsigned int GetHeight() const { return _height; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << _width << ", " << _height;
			return ss.str();
		}

		static EventType GetStaticType() { return EventType::WindowResized; }
		virtual EventType GetType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "WindowResizeEvent"; }
		virtual int GetCategoryFlags() const override { return EventCategoryApplication; }
	private:
		unsigned int _width,_height;
	};

	class WindowMoveEvent : public Event
	{
	public:
		WindowMoveEvent(unsigned int x,unsigned int y) : _x(x),_y(y) {}

		unsigned int GetWidth() const { return _x; }
		unsigned int GetHeight() const { return _y; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowMoveEvent: " << _x << ", " << _y;
			return ss.str();
		}

		static EventType GetStaticType() { return EventType::WindowMoved; }
		virtual EventType GetType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "WindowMoveEvent"; }
		virtual int GetCategoryFlags() const override { return EventCategoryApplication; }
	private:
		unsigned int _x,_y;
	};

	class WindowFocusEvent : public Event
	{
	public:
		WindowFocusEvent() = default;

		std::string ToString() const override
		{
			return "WindowFocusEvent";
		}

		static EventType GetStaticType() { return EventType::WindowFocus; }
		virtual EventType GetType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "WindowFocusEvent"; }
		virtual int GetCategoryFlags() const override { return EventCategoryApplication; }
	};

	class WindowFocusLostEvent : public Event
	{
	public:
		WindowFocusLostEvent() = default;

		std::string ToString() const override
		{
			return "WindowFocusLostEvent";
		}

		static EventType GetStaticType() { return EventType::WindowFocusLost; }
		virtual EventType GetType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "WindowFocusLostEvent"; }
		virtual int GetCategoryFlags() const override { return EventCategoryApplication; }
	};

	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() = default;

		std::string ToString() const override
		{
			return "WindowCloseEvent";
		}

		static EventType GetStaticType() { return EventType::WindowClosed; }
		virtual EventType GetType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "WindowCloseEvent"; }
		virtual int GetCategoryFlags() const override { return EventCategoryApplication; }
	};

	class GameTickEvent : public Event
	{
	public:
		GameTickEvent() = default;

		std::string ToString() const override
		{
			return "GameTickEvent";
		}

		static EventType GetStaticType() { return EventType::GameTick; }
		virtual EventType GetType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "GameTickEvent"; }
		virtual int GetCategoryFlags() const override { return EventCategoryApplication; }
	};

	class GameUpdateEvent : public Event
	{
	public:
		GameUpdateEvent() = default;

		std::string ToString() const override
		{
			return "GameUpdateEvent";
		}

		static EventType GetStaticType() { return EventType::GameUpdate; }
		virtual EventType GetType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "GameUpdateEvent"; }
		virtual int GetCategoryFlags() const override { return EventCategoryApplication; }
	};

	class GameRenderEvent : public Event
	{
	public:
		GameRenderEvent() = default;

		std::string ToString() const override
		{
			return "GameRenderEvent";
		}

		static EventType GetStaticType() { return EventType::GameRender; }
		virtual EventType GetType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "GameRenderEvent"; }
		virtual int GetCategoryFlags() const override { return EventCategoryApplication; }
	};
}