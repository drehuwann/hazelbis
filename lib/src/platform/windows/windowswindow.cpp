#include "hzpch.h"

#include "windowswindow.h"

namespace Hazel {
    static bool s_GLFWInitialized = false;

    Window *Window::Create(const WindowProps &props) {
        return new WindowsWindow(props);
    }

    WindowsWindow::WindowsWindow(const WindowProps &props) {
        Init(props);
    }

    WindowsWindow::~WindowsWindow() {
        Shutdown();
    }

    void WindowsWindow::Init(const WindowProps &props) {
        mData.title = props.title;
        mData.width = props.width;
        mData.height = props.height;
        Logger::Info("Creating window '%s' of size (%d, %d) . Object %s resides at 0x%p", mData.title.c_str(), mData.width, mData.height, typeid(this).name(), this);
        if (! s_GLFWInitialized) {
            //TODO : GLFW terminate on shutdown.
            int success = glfwInit();
            HZ_CORE_ASSERT(success, "Could not initialize GLFW !");
            s_GLFWInitialized = true;
        }
        mWindow = glfwCreateWindow((int)props.width, (int)props.height, props.title.c_str(), nullptr, nullptr);
        glfwSetWindowUserPointer(mWindow, &mData);
        SetVsync(true);
        glfwMakeContextCurrent(mWindow);
        Logger::Info("Succesfully initialized %s at 0x%p", typeid(mWindow).name(), &mWindow);
    }

    void WindowsWindow::Shutdown() {
        if (s_GLFWInitialized) {
            glfwDestroyWindow(mWindow);
        }
    }

    void WindowsWindow::OnUpdate() {
        glfwPollEvents();
        glfwSwapBuffers(mWindow);
    }

    void WindowsWindow::SetVsync(bool enabled) {
        if (enabled) {
            glfwSwapInterval(1);
        } else {
            glfwSwapInterval(0);
        }
        mData.vSync = enabled;
    }

    bool WindowsWindow::IsVsync() const {
        return mData.vSync;
    }
}
