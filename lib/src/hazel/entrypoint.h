#pragma once

#ifdef HZ_PLATFORM_WINDOWS

extern Hazel::Application *Hazel::CreateApplication();

int main(int argc, char **argv) {
    auto app = Hazel::CreateApplication();
    app->Run();
    if (app) delete app;
    app = nullptr;
}

#endif  // HZ_PLATFORM_WINDOWS
