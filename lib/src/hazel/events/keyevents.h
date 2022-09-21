#pragma once

#include "./events.h"
#include "../keycodes.h"

namespace Hazel {

	class KeyEvent : public Event {
	public:
		KeyCode GetKeyCode() const {
            return m_KeyCode;
        }

		EVT_CLASS_CATEGORY(EvtCatKb | EvtCatInput)

	protected:
		KeyEvent(const KeyCode keycode) : m_KeyCode(keycode) {
        }

		KeyCode m_KeyCode;
	};

	class KeyPressedEvent : public KeyEvent {
	public:
		KeyPressedEvent(const KeyCode keycode, bool isRepeat = false) : KeyEvent(keycode), m_IsRepeat(isRepeat) {
			Logger::Trace("Spawning keyPressed(code = %d, repeat = %s) event.", keycode , (isRepeat ? "true" : "false"));
        }

		bool IsRepeat() const {
            return m_IsRepeat;
        }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (repeat = " << m_IsRepeat << ")";
			return ss.str();
		}

		EVT_CLASS_TYPE(KeyPressed)

	private:
		bool m_IsRepeat;
	};

	class KeyReleasedEvent : public KeyEvent {
	public:
		KeyReleasedEvent(const KeyCode keycode) : KeyEvent(keycode) {
			Logger::Trace("Spawning keyReleased(code = %d) event.", keycode);
        }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVT_CLASS_TYPE(KeyReleased)
	};

	class KeyTypedEvent : public KeyEvent {
	public:
		KeyTypedEvent(const KeyCode keycode) : KeyEvent(keycode) {
			Logger::Trace("Spawning keyTyped(code = %d) event.", keycode);
        }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVT_CLASS_TYPE(KeyTyped)
	};
}