#include "Application.hpp"

bool Application::propertyViewIsOpen = true;

Application* Application::instance = nullptr;
Application::~Application()
{
}

void Application::frameBufferCallback(GLFWwindow* window, int width, int height){
    Window* fWindow = (Window*)glfwGetWindowUserPointer(window);
    fWindow->height = height;
    fWindow->width = width;
    instance->Render();
}

EditorView* InitPropertyView(){
    return (EditorView* )(new PropertyView(&Application::propertyViewIsOpen));
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

            Renderer::GetMainCam()->Rotate(glm::vec3(yDif/500, xDif/500, 0));

            mousePos.x = xpos;
            mousePos.y = ypos;
        }
    }
    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE){
        releasedRight = true;
    }
}
void Application::Init(){
    mWindow = new Window("SEngine", 1080, 720, frameBufferCallback);
    glfwSetWindowUserPointer(mWindow->GetWindow(), mWindow);
    glfwSetCursorPosCallback(mWindow->GetWindow(), CursorPosCallback);
    Renderer::Init();
    ui = new UI();
    ui->init(mWindow);
    ViewBuilder::AddViewInitializer(InitPropertyView);
    ViewBuilder::Build();
    LoggingSystem::Init();
    CONSOLE_LOG_INFO("Logging system initialized!");
}


void Application::ProcessInput(){
    if (glfwGetKey(mWindow->GetWindow(), GLFW_KEY_W)){
        Renderer::GetMainCam()->Move(glm::vec3(0, 0, 0.02f));
    }
    if (glfwGetKey(mWindow->GetWindow(), GLFW_KEY_S))
    {
        Renderer::GetMainCam()->Move(glm::vec3(0, 0, -0.02f));
    }

    if (glfwGetKey(mWindow->GetWindow(), GLFW_KEY_D)){
        Renderer::GetMainCam()->Move(glm::vec3(-0.02f, 0, 0));
    }
    if (glfwGetKey(mWindow->GetWindow(), GLFW_KEY_A))
    {
        Renderer::GetMainCam()->Move(glm::vec3(0.02f, 0, 0));
    }

    if (glfwGetKey(mWindow->GetWindow(), GLFW_KEY_E)){
        Renderer::GetMainCam()->Move(glm::vec3(0, 0.02f, 0));
    }
    if (glfwGetKey(mWindow->GetWindow(), GLFW_KEY_Q))
    {
        Renderer::GetMainCam()->Move(glm::vec3(0, -0.02f, 0));
    }
}

void Application::Render(){

    glViewport(0, 0, mWindow->width, mWindow->height);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);


    ui->pre_render();
    for (int i = 0; i < ViewBuilder::GetCount(); i++)
    {
        ViewBuilder::views[i]->Render();
    }
    Renderer::Render();
    ui->post_render();


    glfwPollEvents();
    glfwSwapBuffers(mWindow->GetWindow());
}

void Application::Loop(){
    while (!mWindow->WindowShouldClose())
    {
        ProcessInput();
        Render();
    }
}

void Application::ShutDown(){
    ui->end();
    Renderer::ShutDown();
    delete mWindow;
    glfwTerminate();
    LoggingSystem::ShutDown();
}