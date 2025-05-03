#pragma once
#include <functional>
#include <string>
#include <ostream>

namespace Lobster
{
	enum class EventType
	{
		Custom = 0,
		GameTick, GameUpdate, GameRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseMoved, MouseClicked, MouseReleased, MouseScrolled,
		WindowClosed, WindowFocus, WindowFocusLost, WindowResized, WindowMoved,
	};

	enum EventCategory : int
	{
		EventCategoryCustom        = 0,
		EventCategoryApplication   = 1 << 0,
		EventCategoryInput         = 1 << 1,
		EventCategoryKeyboard      = 1 << 2,
		EventCategoryMouse         = 1 << 3,
		EventCategoryMouseButton   = 1 << 4,
	};

	class Event
	{
		friend class EventDispatcher;
	public:
		virtual ~Event() = default;
		virtual EventType GetType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;

		virtual std::string ToString() const { return GetName(); }

		inline bool IsConsumed() { return handled; }
		inline bool IsInCategory(EventCategory category) { return GetCategoryFlags() & category; }
	protected:
		bool handled = false;
	};

	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event);

		template<typename T>
		bool Dispatch(EventFn<T> func);
	private:
		Event& _event;
	};

	inline std::ostream& operator<<(std::ostream& os,const Event& e);
}
