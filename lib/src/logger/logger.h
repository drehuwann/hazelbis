#pragma once

#include "hzpch.h"
#include "../hazel/core.h"
#include "../design/singleton.h"

#include <cstdio>
#include <mutex>
#include <ctime>
#include <typeinfo>
#include <source_location>

constexpr const char* baseFilename(const char* path) {
    const char* file = path;
    while (*path) {
        if (*path++ == '\\') {
            file = path;
        }
    }
    return file;
}

class HZ_API Logger : public Singleton<Logger> {
    friend class Singleton<Logger>;
public:
    enum Priority {
		TracePrio,
        DebugPrio,
        InfoPrio,
        WarnPrio,
        ErrorPrio,
        CriticalPrio
	};

    static void SetPriority(Priority newPrio, const std::source_location& loc = std::source_location::current()) {
        Logger *instance = GetInst();
        instance->prio = newPrio;
        instance->Log(InfoPrio, loc, "Log level set to %s", (const char *)(&instance->priorityStr[newPrio]));
    }

    static Priority GetPriority() {
    	return GetInst()->prio;
    }

    static const char *GetPriorityStr() {
    	Logger *instance = GetInst();
    	return (const char *)(&(instance->priorityStr[instance->prio][0]));
    }

    static void SetTimestampFormat(const char* newTimestampFormat) {
    	GetInst()->timeFormat = newTimestampFormat;
    }

    static const char *GetTimestampFormat() {
    	return GetInst()->timeFormat;
    }

    static bool SetFile() {
    	Logger *instance = GetInst();
    	instance->filename = instance->defaultFilename;
	    return instance->EnableFileOutput();
    }
    
    static bool SetFile(const char *filepath) {
    	Logger *instance = GetInst();
    	instance->filename = filepath;
	    return instance->EnableFileOutput();
    }

#define METALOG(_LVL_) \
    template <typename... Args> struct _LVL_ {\
        _LVL_(Args&& ...args, const std::source_location& loc = std::source_location::current()) {\
            GetInst()->Log(##_LVL_##Prio, loc, args...);\
        }\
    };\
    template <typename... Args> _LVL_(Args&&...) -> _LVL_<Args...>;

    METALOG(Trace)    
    METALOG(Debug)    
    METALOG(Info)    
    METALOG(Warn)    
    METALOG(Error)    
    METALOG(Critical)    

#undef METALOG

private:
    Logger() {
    }

    ~Logger() {
        FreeFile();
    }

    using Singleton<Logger>::GetInst;  // encapsulating GetInst() to not use it anymore

    Priority prio = InfoPrio;
    bool lineInfo = false;
    std::mutex loggerMutex;
    const char *filename = nullptr;
    const char *defaultFilename = "log.txt";
    std::FILE *file = nullptr;
    char buffer[80];
	const char* timeFormat = "%T  %d-%m-%Y";
    const char priorityStr[6][10] = {
        "TRACE   \0",
        "DEBUG   \0",
        "INFO    \0",
        "WARNING \0",
        "ERROR   \0",
        "CRITICAL\0"
    };

    template <typename... Args> void Log(Priority msgPrio,  const std::source_location& loc, Args... args) {
        if (prio <= msgPrio) {
            std::time_t currTime = std::time(0);
            std::tm *timeStamp = std::localtime(&currTime);
            std::scoped_lock lock(loggerMutex);
		    std::strftime(buffer, 80, timeFormat, timeStamp);
		    std::printf("%s -> ", buffer);
		    std::printf("%s : ", (const char *)(&(priorityStr[msgPrio][0])));
            std::printf("In %s, at line %d : ", baseFilename(loc.file_name()), loc.line());
		    std::printf(args...);
		    std::printf("\n");
            if (file) {
                std::fprintf(file, "%s -> ", buffer);
		        std::fprintf(file, "%s : ",  (const char *)(&(priorityStr[msgPrio][0])));
                std::fprintf(file, "In %s, at line %d : ", baseFilename(loc.file_name()), loc.line());
		        std::fprintf(file, args...);
		        std::fprintf(file, "\n");
	        }
	    }
    }

    bool EnableFileOutput() {
    	FreeFile();
    	file = std::fopen(filename, "a");
	    if (file == nullptr) {
		    return false;
	    }
	    return true;
    }

    void FreeFile(const std::source_location& loc = std::source_location::current()) {
 	    if (file) {
            GetInst()->Log(InfoPrio, loc, "closing log file %s", filename);
            std::fclose(file);
            file = nullptr;
	    }   
    }
};
