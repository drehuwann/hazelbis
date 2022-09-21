#pragma once

#include "hzpch.h"

#ifdef HZ_PLATFORM_WINDOWS
    #ifdef HZ_BUILD_DLL
        #define HZ_API __declspec(dllexport)
    #else  // HZ_BUILD_DLL
        #define HZ_API __declspec(dllimport)
    #endif  // HZ_BUILD_DLL
#else  // HZ_PLATFORM_WINDOWS
    #error WIN Only !
#endif  // HZ_PLATFORM_WINDOWS

#ifdef HZ_DEBUG
	#if defined(HZ_PLATFORM_WINDOWS)
		#define HZ_DEBUGBREAK() __debugbreak()
	#elif defined(HZ_PLATFORM_LINUX)
		#include <signal.h>
		#define HZ_DEBUGBREAK() raise(SIGTRAP)
	#else  // HZ_PLATFORM_*
		#error "Platform doesn't support debugbreak yet!"
	#endif  // HZ_PLATFORM_*
	#define HZ_ENABLE_ASSERTS
#else  // HZ_DEBUG
	#define HZ_DEBUGBREAK()
#endif  // HZ_DEBUG

#define HZ_EXPAND_MACRO(x) x
#define HZ_STRINGIFY_MACRO(x) #x

#if defined(_MSC_VER)
    #define DISABLE_WARNING_PUSH            __pragma(warning( push ))
    #define DISABLE_WARNING_POP             __pragma(warning( pop )) 
    #define DISABLE_WARNING(warningNumber)  __pragma(warning( disable : warningNumber ))

    #define DISABLE_WARNING_UNREFERENCED_FORMAL_PARAMETER   DISABLE_WARNING(4100)
    #define DISABLE_WARNING_UNREFERENCED_FUNCTION           DISABLE_WARNING(4505)
    // other warnings you want to deactivate...
    #define DISABLE_WARNING_NOT_ALL_PATHS_RETURN            DISABLE_WARNING(4715)                    
#elif defined(__GNUC__) || defined(__clang__)
    #define DO_PRAGMA(X) _Pragma(#X)
    #define DISABLE_WARNING_PUSH            DO_PRAGMA(GCC diagnostic push)
    #define DISABLE_WARNING_POP             DO_PRAGMA(GCC diagnostic pop) 
    #define DISABLE_WARNING(warningName)    DO_PRAGMA(GCC diagnostic ignored #warningName)
    
    #define DISABLE_WARNING_UNREFERENCED_FORMAL_PARAMETER   DISABLE_WARNING(-Wunused-parameter)
    #define DISABLE_WARNING_UNREFERENCED_FUNCTION           DISABLE_WARNING(-Wunused-function)
   // other warnings you want to deactivate... 
    #define DISABLE_WARNING_NOT_ALL_PATHS_RETURN            DISABLE_WARNING(-Wreturn-type)                
#else  // _MSC_VER || _GNUC__ || __clang__
    #define DISABLE_WARNING_PUSH
    #define DISABLE_WARNING_POP
    #define DISABLE_WARNING_UNREFERENCED_FORMAL_PARAMETER
    #define DISABLE_WARNING_UNREFERENCED_FUNCTION
    // other warnings you want to deactivate... 
    #define DISABLE_WARNING_NOT_ALL_PATHS_RETURN
#endif  // _MSC_VER || _GNUC__ || __clang__
