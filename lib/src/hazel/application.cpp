#include "hzpch.h"
#include "./application.h"
namespace Hazel {

    Application::Application() {
    }
    
    Application::~Application() {
    }

    void Application::Run() {
        Logger::Info("Launching Application instanciated at 0x%p", this);
        Logger::SetPriority(Logger::TracePrio);
        WindResizeEvent(1280, 720);
        while (true);
    }
}
