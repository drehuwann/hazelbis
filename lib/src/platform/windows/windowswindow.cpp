#include "hzpch.h"

#include "windowswindow.h"

namespace Hazel {
    static bool s_GLFWInitialized = false;
    static void GLFWErrorCallback(int error, const char *description) {
        Logger::Error("GLFW error %d : %s", error, description);
    }

    Window *Window::Create(const WindowProps &props) {
        return new WindowsWindow(props);
    }

    WindowsWindow::WindowsWindow(const WindowProps &props) {
        Init(props);
    }

    WindowsWindow::~WindowsWindow() {
        Shutdown();
        glfwTerminate();
    }

    void WindowsWindow::Init(const WindowProps &props) {
        mData.title = props.title;
        mData.width = props.width;
        mData.height = props.height;
        Logger::Info("Creating window '%s' of size (%d, %d) . Object %s resides at 0x%p", mData.title.c_str(), mData.width, mData.height, typeid(this).name(), this);
        if (! s_GLFWInitialized) {
            int success = glfwInit();
            HZ_CORE_ASSERT(success, "Could not initialize GLFW !");
            glfwSetErrorCallback(GLFWErrorCallback);
            s_GLFWInitialized = true;
        }
        mWindow = glfwCreateWindow((int)props.width, (int)props.height, props.title.c_str(), nullptr, nullptr);
        glfwSetWindowUserPointer(mWindow, &mData);
        SetVsync(true);

        //Set callbacks :
        glfwSetWindowSizeCallback(mWindow, [] (GLFWwindow *window, int width, int height) {
            WindowData &data = *((WindowData *)glfwGetWindowUserPointer(window));
            data.width= (unsigned int)width;
            data.height = (unsigned int)height;
            WindResizeEvent event(width, height);
            data.evtCallback(event);
        });
        
        glfwSetWindowCloseCallback(mWindow, [] (GLFWwindow *window) {
            WindowData &data = *((WindowData *)glfwGetWindowUserPointer(window));
            WindCloseEvent event;
            data.evtCallback(event);
        });

        glfwSetKeyCallback(mWindow, [] (GLFWwindow* window, int key, int scancode, int action, int mods) {
            WindowData &data = *((WindowData *)glfwGetWindowUserPointer(window));
            switch(action) {
                case GLFW_PRESS : {
                    KeyPressedEvent event(key, false);
                    data.evtCallback(event);
                    break;
                }
                case GLFW_RELEASE : {
                    KeyReleasedEvent event(key);
                    data.evtCallback(event);
                    break;
                    }
                case GLFW_REPEAT : {
                    KeyPressedEvent event(key, true);
                    data.evtCallback(event);
                    break;
                }
            }
        });

        glfwSetMouseButtonCallback(mWindow, [] (GLFWwindow* window, int button, int action, int mods) {
            WindowData &data = *((WindowData *)glfwGetWindowUserPointer(window));
            switch(action) {
                case GLFW_PRESS : {
                    MouseButtonPressedEvent event(button);
                    data.evtCallback(event);
                    break;
                }
                case GLFW_RELEASE : {
                    MouseButtonReleasedEvent event(button);
                    data.evtCallback(event);
                    break;
                    }
            }
        });

        glfwSetScrollCallback(mWindow, [] (GLFWwindow* window, double xoffset, double yoffset) {
            WindowData &data = *((WindowData *)glfwGetWindowUserPointer(window));
            MouseScrolledEvent event((float)xoffset, (float)yoffset);
            data.evtCallback(event);
        });

        glfwSetCursorPosCallback(mWindow, [] (GLFWwindow* window, double xpos, double ypos) {
            WindowData &data = *((WindowData *)glfwGetWindowUserPointer(window));
            MouseMovedEvent event((float)xpos, (float)ypos);
            data.evtCallback(event);
        });

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
