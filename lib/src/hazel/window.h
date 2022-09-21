#pragma once

#include "./hzpch.h"

#include "hazel/core.h"
#include "hazel/events/events.h"

namespace Hazel {

    struct WindowProps {
        std::string title;
        unsigned int width;
        unsigned int height;
        WindowProps(const std::string tit = "Hazel(bis) Engine",
                    unsigned int wid = 1280, unsigned int hei = 720)
                : title(tit), width(wid), height(hei) {
        }
    };

    class HZ_API Window {
    public:
        using EventCallbackFn = std::function<void(Event&)>;

        virtual ~Window() {
        }

        virtual void OnUpdate() = 0;

        virtual unsigned int GetWidth() const = 0;
        virtual unsigned int GetHeight() const = 0;

        virtual void SetEventCallback(const EventCallbackFn &callback) = 0;
        virtual void SetVsync(bool enabled) = 0;
        virtual bool IsVsync() const = 0;

        static Window *Create(const WindowProps &props = WindowProps());
    };
}