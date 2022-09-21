#include "hzpch.h"

#include "application.h"

namespace Hazel {
    Application::Application() {
        mWindow = std::unique_ptr<Window>(Window::Create());
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
}
