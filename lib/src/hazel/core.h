#pragma once

#ifdef HZ_PLATFORM_WINDOWS
    #ifdef HZ_BUILD_DLL
        #define HZ_API __declspec(dllexport)
    #else  // HZ_BUILD_DLL
        #define HZ_API __declspec(dllimport)
    #endif  // HZ_BUILD_DLL
#else  // HZ_PLATFORM_WINDOWS
    #error WIN Only !
#endif  // HZ_PLATFORM_WINDOWS
