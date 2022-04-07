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

MainWindow::MainWindow(const char* title, int width, int height, RenderFunc func) : Window(title, width, height, OnResize){
    renderFunc = func;
    glfwSetWindowUserPointer(GetWindow(), this);
}

MainWindow::~MainWindow()
{
}
