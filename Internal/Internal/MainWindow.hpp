#pragma once

#include "Window.hpp"
namespace SEngine_Internal{
typedef void (* RenderFunc)();

class MainWindow : public Window
{
private:
    static bool sceneIsOpen;
    static bool propertyIsOpen;
    static bool debugIsOpen;
    static RenderFunc renderFunc;
    static void OnResize(GLFWwindow* window, int width, int height);
public:
    MainWindow(const char* title, int width, int height, RenderFunc func);
    ~MainWindow();
};
}