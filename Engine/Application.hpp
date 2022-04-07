#include<iostream>
#include "Internal/Render/Renderer.hpp"
#include "Utils/LoggingSystem.hpp"
#include "Log.h"

class Application
{
private:
    Window* mWindow;
    UI* ui;
    void ProcessInput();
public:
    Application() : mWindow(nullptr), ui(nullptr){}
    void Init();
    void Loop();
    void Render();
    ~Application();
    static void frameBufferCallback(GLFWwindow* window, int width, int height);
    static Application* instance;
    static bool propertyViewIsOpen;
    static bool sceneViewIsOpen;
    static bool debugViewIsOpen;
};

