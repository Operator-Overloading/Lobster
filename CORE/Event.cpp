#include "Event.h"

namespace Lobster
{
	EventDispatcher::EventDispatcher(Event& event) : _event(event) {}

	template<typename T>
	bool EventDispatcher::Dispatch(EventFn<T> func)
	{
		if(_event.GetType() == T::GetStaticType())
		{
			_event.handled |= func(*(T*)&_event);
			return true;
		}
		return false;
	}

	std::ostream& operator<<(std::ostream& os,const Event& e)
	{
		return os << e.ToString();
	}
}