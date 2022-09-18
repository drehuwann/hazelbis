#include "application.h"

namespace Hazel {
    Application::Application() {
    }
    
    Application::~Application() {
    }

    void Application::Run() {
        Logger::Info("Launching Application instanciated at 0x%p", this);
        while (true);
    }
}
