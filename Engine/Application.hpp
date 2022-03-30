#include<iostream>
#include "Internal/Renderer.hpp"
#include "Internal/PropertyView.hpp"

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
};

