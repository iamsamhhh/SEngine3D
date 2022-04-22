#pragma once
#include<iostream>
#include "MainWindow.hpp"
#include "UI.hpp"
#include "Application.hpp"

namespace SEngine_Internal{
class Engine
{
private:
    Window* mWindow;
    UI* ui;
    SEngine::Application* app;
    void ProcessInput();
public:
    Engine() : mWindow(nullptr), ui(nullptr){}
    void Init();
    void Loop();
    void Render();
    ~Engine();
    static void frameBufferCallback(GLFWwindow* window, int width, int height);
    static Engine* instance;
};
}