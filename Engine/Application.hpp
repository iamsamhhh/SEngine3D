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
    void ProcessInput();
    void Render();
public:
    Application() : mWindow(nullptr), ui(nullptr){}
    void Init();
    void Loop();
    ~Application();
    static void frameBufferCallback(GLFWwindow* window, int width, int height);
    static Application* instance;
    static bool propertyViewIsOpen;
    static bool sceneViewIsOpen;
    static bool debugViewIsOpen;
};

