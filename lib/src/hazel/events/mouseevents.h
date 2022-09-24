#pragma once

#include "hzpch.h"

#include "events.h"
#include "mousecodes.h"

namespace Hazel {
	class MouseMovedEvent : public Event {
	public:
		MouseMovedEvent(const float x, const float y) : m_MouseX(x), m_MouseY(y) {
            Logger::Info("Spawning mousemoved(%f, %f) event.", x, y);
        }

		float GetX() const {
            return m_MouseX;
        }
		float GetY() const {
            return m_MouseY;
        }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}

		EVT_CLASS_TYPE(MouseMoved)
		EVT_CLASS_CATEGORY(EvtCatMouse | EvtCatInput)

	private:
		float m_MouseX, m_MouseY;
	};

	class MouseScrolledEvent : public Event {
	public:
		MouseScrolledEvent(const float xOffset, const float yOffset) : m_XOffset(xOffset), m_YOffset(yOffset) {
            Logger::Info("Spawning mouseScrolled(%f, %f) event.", xOffset, yOffset);
        }

		float GetXOffset() const {
            return m_XOffset;
        }
		float GetYOffset() const {
            return m_YOffset;
        }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
			return ss.str();
		}

		EVT_CLASS_TYPE(MouseScrolled)
		EVT_CLASS_CATEGORY(EvtCatMouse | EvtCatInput)

	private:
		float m_XOffset, m_YOffset;
	};

	class MouseButtonEvent : public Event {
	public:
		MouseCode GetMouseButton() const {
            return m_Button;
        }

		EVT_CLASS_CATEGORY(EvtCatMouse | EvtCatInput | EvtCatMouseBtn)

	protected:
		MouseButtonEvent(const MouseCode button) : m_Button(button) {
        }

		MouseCode m_Button;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent {
	public:
		MouseButtonPressedEvent(const MouseCode button) : MouseButtonEvent(button) {
            Logger::Info("Spawning mouseBtnPressed(%d) event.", button);
        }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_Button;
			return ss.str();
		}

		EVT_CLASS_TYPE(MouseBtnPressed)
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent {
	public:
		MouseButtonReleasedEvent(const MouseCode button) : MouseButtonEvent(button) {
            Logger::Info("Spawning mouseBtnReleased(%d) event.", button);
        }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_Button;
			return ss.str();
		}

		EVT_CLASS_TYPE(MouseBtnReleased)
	};
}
