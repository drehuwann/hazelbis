#pragma once

#include "hzpch.h"

#include "hazel/window.h"
#include "assert.h"

#include "../../glfw/include/GLFW/glfw3.h"

namespace Hazel {
    class WindowsWindow : public Window {
    public:
        WindowsWindow(const WindowProps &props);
        virtual ~WindowsWindow();

        void OnUpdate() override;
        
        inline unsigned int GetWidth() const override {return mData.width;}
        inline unsigned int GetHeight() const override {return mData.height;}

        inline void SetEventCallback(const EventCallbackFn &callback) override {mData.evtCallback = callback;}
        virtual void SetVsync(bool enabled);
        virtual bool IsVsync() const;

    private:
        virtual void Init(const WindowProps &props);
        virtual void Shutdown();
        GLFWwindow *mWindow;

        struct WindowData {
            std::string title;
            unsigned int width, height;
            bool vSync;

            EventCallbackFn evtCallback;
        };

        WindowData mData;
    };
}