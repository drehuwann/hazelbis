#pragma once

#include <String>
#include <sstream>
#include <functional>

#include "../core.h"
#include "../logger/logger.h"

namespace Hazel {
    enum class EventType {
        None = 0,
        WindClose, WindResize, WindFocus, WindLostFocus, WindMoved,
        AppTick, AppUpdate, AppRender, 
        KeyPressed, KeyReleased, KeyTyped,
        MouseBtnPressed, MouseBtnReleased, MouseMoved, MouseScrolled
    };

    enum EventCategory {
        EvtCatNonr = 0,
        EvtCatAppli = 1,
        EvtCatInput = 1 << 2,
        EvtCatKb = 1 << 3,
        EvtCatMouse = 1 << 4,
        EvtCatMouseBtn = 1 << 5
    };

    #define EVT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; } \
        virtual EventType GetEventType() const override { return GetStaticType(); } \
        virtual const char *GetName() const override { return #type; }

    #define EVT_CLASS_CATEGORY(categ) virtual int GetCategFlags() const override { return categ; }

    class HZ_API Event {
        friend class EventDispatcher;
    public:
        virtual ~Event() = default;
        
        bool Handled = false;

		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		bool IsInCategory(EventCategory category)
		{
			return GetCategFlags() & category;
		}
    };

    class HZ_API EventDispatcher {
        friend class Event;
	public:
		EventDispatcher(Event& event) : m_Event(event) {
		}
		
		template<typename T, typename F> bool Dispatch(const F& func) {
			if (m_Event.GetEventType() == T::GetStaticType()) {
				m_Event.Handled |= func(static_cast<T&>(m_Event));
				return true;
			}
			return false;
		}

	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e) {
		return os << e.ToString();
	}
}
