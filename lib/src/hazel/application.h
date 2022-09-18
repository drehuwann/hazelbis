#pragma once

#include "core.h"
#include "logger.h"

namespace Hazel {
    class HZ_API Application {
    public:
        Application();
        virtual ~Application();

        void Run();
    };

    // to be defined in client.
    Application *CreateApplication();
}
