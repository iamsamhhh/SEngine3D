#include<iostream>
#include "Internal/Render/Renderer.hpp"
#include "Internal/Window_and_UI/PropertyView.hpp"
#include "Internal/Window_and_UI/SceneView.hpp"
#include "Utils/LoggingSystem.hpp"
#include "Internal/ECS/ECS_Manager.hpp"
#include "Log.h"

class Application
{
private:
    Window* mWindow;
    UI* ui;
public:
    static Application* instance;
    Application() : mWindow(nullptr), ui(nullptr){}
    void Init();
    void Render();
    void Loop();
    void ShutDown();
    void ProcessInput();
    static void frameBufferCallback(GLFWwindow* window, int width, int height);
    ~Application();
    static bool propertyViewIsOpen;
    static bool sceneViewIsOpen;
};

