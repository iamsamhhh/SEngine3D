#include "Internal/Window.hpp"
#include "Log.h"
namespace SEngine_Internal{
bool Window::GLFWInited = false;
Window::Window(const char* title, int scrWidth, int scrHeight, GLFWframebuffersizefun callback) : width(scrWidth), height(scrHeight)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    window = glfwCreateWindow(scrWidth, scrHeight, title, NULL, NULL);

    if (window == NULL)
    {
        CONSOLE_LOG_ERROR("fail to init window");
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, callback);
}

void Window::OnResize(int width, int height){
    this->width = width;
    this->height = height;
}

GLFWwindow* Window::GetWindow(){return window;}

bool Window::WindowShouldClose(){return glfwWindowShouldClose(window);}

Window::~Window(){glfwDestroyWindow(window);}
}