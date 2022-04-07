#include<iostream>
#include "Internal/Render/Renderer.hpp"
#include "Utils/LoggingSystem.hpp"
#include "Log.h"

class Engine
{
private:
    Window* mWindow;
    UI* ui;
    void ProcessInput();
public:
    Engine() : mWindow(nullptr), ui(nullptr){}
    void Init();
    void Loop();
    void Render();
    ~Engine();
    static void frameBufferCallback(GLFWwindow* window, int width, int height);
    static Engine* instance;
    static bool propertyViewIsOpen;
    static bool sceneViewIsOpen;
    static bool debugViewIsOpen;
};

