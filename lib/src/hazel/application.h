#pragma once

#include "hzpch.h"

#include "core.h"
#include "logger/logger.h"
#include "events/appevents.h"
#include "events/keyevents.h"
#include "events/mouseevents.h"
#include "window.h"

#include "../../glfw/include/GLFW/glfw3.h"

namespace Hazel {
    class HZ_API Application {
    public:
        Application();
        virtual ~Application();

        void Run();
        void OnEvent(Event &e);

    private:
        std::unique_ptr<Window> mWindow;
        bool mRunning = true;
    };

    // to be defined in client.
    Application *CreateApplication();
}
