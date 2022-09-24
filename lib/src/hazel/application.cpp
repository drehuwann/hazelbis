#include "hzpch.h"

#include "application.h"

#define BIND_EVT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

namespace Hazel {
    Application::Application() {
        mWindow = std::unique_ptr<Window>(Window::Create());
        mWindow->SetEventCallback(BIND_EVT_FN(OnEvent));
    }
    
    Application::~Application() {
    }

    void Application::Run() {
        while (mRunning) {
            glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            mWindow->OnUpdate();
        }
    }

    void Application::OnEvent(Event &e) {
        Logger::Trace("Treating %s event %s", typeid(e).name(), e.GetName());
    }
}
