#include "../Render/Renderer.hpp"
#include "MainWindow.hpp"

RenderFunc MainWindow::renderFunc = nullptr;

void MainWindow::OnResize(GLFWwindow* window, int width, int height){
    Window* fWindow = (Window*)glfwGetWindowUserPointer(window);
    fWindow->height = height;
    fWindow->width = width;
    if (renderFunc){
        renderFunc();
    }
}
glm::vec2 mousePos = glm::vec2(0);
bool releasedRight = true;
void CursorPosCallback(GLFWwindow* window, double xpos, double ypos){

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS){
        if (releasedRight)
        {
            mousePos.x = xpos;
            mousePos.y = ypos;
            releasedRight = false;
        }
        else{
            double xDif = xpos - mousePos.x;
            double yDif = ypos - mousePos.y;

            Renderer::GetMainCam()->Rotate(glm::vec3(xDif/500, yDif/500, 0));

            mousePos.x = xpos;
            mousePos.y = ypos;
        }
    }
    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE){
        releasedRight = true;
    }
}
MainWindow::MainWindow(const char* title, int width, int height, RenderFunc func) : Window(title, width, height, OnResize){
    renderFunc = func;
    glfwSetWindowUserPointer(GetWindow(), this);
    glfwSetCursorPosCallback(GetWindow(), CursorPosCallback);
}

MainWindow::~MainWindow()
{
}
