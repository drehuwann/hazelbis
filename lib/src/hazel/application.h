#pragma once

#include "hzpch.h"
#include "./core.h"
#include "../logger/logger.h"
#include "events/appevents.h"
#include "events/keyevents.h"
#include "events/mouseevents.h"
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
