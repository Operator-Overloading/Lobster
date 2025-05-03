#pragma once
#include "Event.h"
#include "KeyCode.h"

#include <sstream>

namespace Lobster
{
	class KeyEvent : public Event
	{
	public:
		KeyCode GetKeyCode() const { return _keycode; }

		virtual int GetCategoryFlags() const override { return EventCategoryInput | EventCategoryKeyboard; }
	protected:
		KeyEvent(const KeyCode keycode) : _keycode(keycode) {}

		KeyCode _keycode;
	};

	class KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(const KeyCode keycode,bool isRepeat = false) : KeyEvent(keycode),_is_repeat(isRepeat) {}

		bool IsRepeat() const { return _is_repeat; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << _keycode << " (repeat = " << _is_repeat << ")";
			return ss.str();
		}

		static EventType GetStaticType() { return EventType::KeyPressed; }
		virtual EventType GetType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "KeyPressedEvent"; }
	private:
		bool _is_repeat;
	};

	class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(const KeyCode keycode) : KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << _keycode;
			return ss.str();
		}

		static EventType GetStaticType() { return EventType::KeyReleased; }
		virtual EventType GetType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "KeyReleasedEvent"; }
	};

	class KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(const KeyCode keycode) : KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << _keycode;
			return ss.str();
		}

		static EventType GetStaticType() { return EventType::KeyTyped; }
		virtual EventType GetType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "KeyTypedEvent"; }
	};

	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(const float x,const float y) : _x(x),_y(y) {}

		float GetX() const { return _x; }
		float GetY() const { return _y; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << _x << ", " << _y;
			return ss.str();
		}

		static EventType GetStaticType() { return EventType::MouseMoved; }
		virtual EventType GetType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "MouseMovedEvent"; }
		virtual int GetCategoryFlags() const override { return EventCategoryInput | EventCategoryMouse; }
	private:
		float _x,_y;
	};

	class MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(const float offset_x,const float offset_y) : _offset_x(offset_x),_offset_y(offset_y) {}

		float GetXOffset() const { return _offset_x; }
		float GetYOffset() const { return _offset_y; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
			return ss.str();
		}

		static EventType GetStaticType() { return EventType::MouseScrolled; }
		virtual EventType GetType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "MouseScrolledEvent"; }
		virtual int GetCategoryFlags() const override { return EventCategoryInput | EventCategoryMouse; }
	private:
		float _offset_x,_offset_y;
	};

	class MouseButtonEvent : public Event
	{
	public:
		MouseCode GetMouseButton() const { return _button; }
	protected:
		MouseButtonEvent(const MouseCode button) : _button(button) {}

		MouseCode _button;

		virtual int GetCategoryFlags() const override { return EventCategoryInput | EventCategoryMouse | EventCategoryMouseButton; }
	};

	class MouseClickedEvent : public MouseButtonEvent
	{
	public:
		MouseClickedEvent(const MouseCode button) : MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseClickedEvent: " << _button;
			return ss.str();
		}

		static EventType GetStaticType() { return EventType::MouseClicked; }
		virtual EventType GetType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "MouseClickedEvent"; }
	};

	class MouseReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseReleasedEvent(const MouseCode button) : MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseReleasedEvent: " << _button;
			return ss.str();
		}

		static EventType GetStaticType() { return EventType::MouseReleased; }
		virtual EventType GetType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "MouseReleasedEvent"; }
	};
}