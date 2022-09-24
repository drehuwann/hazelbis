#pragma once

#include "hzpch.h"

#include "events.h"

namespace Hazel {
	class WindResizeEvent : public Event
	{
	public:
		WindResizeEvent(unsigned int width, unsigned int height) : m_Width(width), m_Height(height) {
			Logger::Info("Spawning windResize(%d, %d) event.", width, height);
        }

		unsigned int GetWidth() const {
            return m_Width;
        }
		unsigned int GetHeight() const {
            return m_Height;
        }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}

		EVT_CLASS_TYPE(WindResize)
		EVT_CLASS_CATEGORY(EvtCatAppli)

	private:
		unsigned int m_Width, m_Height;
	};

	class WindCloseEvent : public Event {
	public:
		WindCloseEvent() = default;

		EVT_CLASS_TYPE(WindClose)
		EVT_CLASS_CATEGORY(EvtCatAppli)
	};

	class AppTickEvent : public Event {
	public:
		AppTickEvent() = default;

		EVT_CLASS_TYPE(AppTick)
		EVT_CLASS_CATEGORY(EvtCatAppli)
	};

	class AppUpdateEvent : public Event {
	public:
		AppUpdateEvent() = default;

		EVT_CLASS_TYPE(AppUpdate)
		EVT_CLASS_CATEGORY(EvtCatAppli)
	};

	class AppRenderEvent : public Event {
	public:
		AppRenderEvent() = default;

		EVT_CLASS_TYPE(AppRender)
		EVT_CLASS_CATEGORY(EvtCatAppli)
	};
}
