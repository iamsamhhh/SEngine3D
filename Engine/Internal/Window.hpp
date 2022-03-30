#include<GLFW/glfw3.h>
#include<iostream>

class Window
{
private:
    static bool GLFWInited;
    GLFWwindow* window;
    
public:
    int width, height;
    bool WindowShouldClose();
    GLFWwindow* GetWindow();
    void OnResize(int width, int height);
    static void MakeWindowCurrent(GLFWwindow* window);
    Window(const char* title, int scrWidth, int scrHeight, GLFWframebuffersizefun callback);
    ~Window();
};