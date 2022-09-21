#pragma once

#ifdef HZ_PLATFORM_WINDOWS

#include "hzpch.h"

#include "application.h"

extern Hazel::Application *Hazel::CreateApplication();

int main(int argc, char **argv) {
    if (argc == 1) { //launch default console Log
        const char *logLevel = Logger::GetPriorityStr();
        Logger::Info("Lauching Sandbox with no arguments => Console logging at level %s", logLevel);
    } else {
        Logger::Info("Launching Sandbox with %d arguments", argc - 1);
        const char *argToParse = nullptr;
        char parsedChar = 0;
        enum {BAD, OPTION, FILENAME} argType;
        bool waitFilename = false;
        const char *filename = nullptr;
        const char *savedArg = nullptr;
        while (++argv && (argToParse = (const char *)(*argv))) {
            savedArg = argToParse;
            argType = BAD;
            Logger::Info("Parsing arg %s", argToParse);
            while (argToParse && (parsedChar = *(argToParse ++))) {
                Logger::Debug("parsing '%c' character", parsedChar);
                if (argType == OPTION) {
                    switch(parsedChar) {
                        case 'T' :
                            Logger::SetPriority(Logger::TracePrio);
                            break;
                        case 'D' :
                            Logger::SetPriority(Logger::DebugPrio);
                            break;
                        case 'I' :
                            Logger::SetPriority(Logger::InfoPrio);
                            break;
                        case 'W' :
                            Logger::SetPriority(Logger::WarnPrio);
                            break;
                        case 'E' :
                            Logger::SetPriority(Logger::ErrorPrio);
                            break;
                        case 'C' :
                            Logger::SetPriority(Logger::CriticalPrio);
                            break;
                        case 'f' :
                            waitFilename = true;
                            break;
                        default  :
                            Logger::Warn("Ill-formed parameter : '%c' (0x%x) irrelevant here", parsedChar, parsedChar);
                            argType = BAD;
                    };
                } else if (argType != FILENAME && parsedChar == '-') {
                    argType = OPTION;
                } else {
                    argType = FILENAME;
                    if (parsedChar < 32 || parsedChar > 127 || parsedChar == '<' || parsedChar == '>' || parsedChar == ':'
                            || parsedChar == '"' || parsedChar == '|' || parsedChar == '?' || parsedChar == '*') {
                        Logger::Warn("Illegal character in filename : %c (0x%x). Ignoring arg.", parsedChar, parsedChar);
                        argType = BAD;
                    }
                }
                if (argType == BAD) break;
            }
            if (argType == FILENAME) filename = savedArg;
        }
        if (waitFilename) {
            if (filename) {
                if (Logger::SetFile(filename)) {
                    Logger::Info("Enabled file logging to '%s'", filename);
                } else {
                    Logger::Warn("Failed to enable file logging to '%s'", filename);
                }
            } else {
                if (Logger::SetFile()) {
                    Logger::Info("Enabled file logging to default file");
                } else {
                    Logger::Warn("Failed to enable logging to default file");
                }
            }
        } else {
            if (filename) {
                Logger::Warn("missing -f parameter. File Logging disabled, arg '%s' ignored.", filename);
            }
        }
    }
    auto app = Hazel::CreateApplication();
    app->Run();
    if (app) delete app;
    app = nullptr;
}

#endif  // HZ_PLATFORM_WINDOWS
