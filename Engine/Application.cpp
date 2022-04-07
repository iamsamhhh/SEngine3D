#include "Application.hpp"
#include "Internal/ECS/Transform.hpp"
#include "Internal/ECS/MoveSystem.hpp"
#include "Internal/ECS/RenderSystem.hpp"
#include "Internal/ECS/Mesh.hpp"
#include "Internal/ECS/MeshRenderer.hpp"
#include "Utils/DebugView.hpp"
#include "Utils/Debug.hpp"
#include "Internal/Window_and_UI/MainWindow.hpp"
#include "Utils/Default.hpp"

bool Application::propertyViewIsOpen = true;
bool Application::sceneViewIsOpen = true;
bool Application::debugViewIsOpen = true;

Application* Application::instance = nullptr;
Application::~Application()
{
    ui->end();
    Renderer::ShutDown();
    delete mWindow;
    glfwTerminate();
    LoggingSystem::ShutDown();
}

// TODO: Should move into window
// void Application::frameBufferCallback(GLFWwindow* window, int width, int height){
//     Window* fWindow = (Window*)glfwGetWindowUserPointer(window);
//     fWindow->height = height;
//     fWindow->width = width;
//     instance->Render();
// }

// TODO: why is this even in application??
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

void RenderAll(){
    Application::instance->Render();
}

// TODO: there is so many things going on here. find a way to clean this
void Application::Init(){

    // -------------------------------------Window init----------------=-----------------------
    mWindow = new MainWindow("SEngine", 1080, 720, RenderAll);
    glfwSetCursorPosCallback(mWindow->GetWindow(), CursorPosCallback);

    // ------------------------------------Renderer init---------------------------------------
    Renderer::Init();

    // ----------------------------------------UI init-----------------------------------------
    ui = new UI();
    ui->init(mWindow);

    //---------------------------------------Logging init--------------------------------------
    LoggingSystem::Init();
    CONSOLE_LOG_INFO("Logging system initialized!");

    Default::Generate();

    CONSOLE_LOG_INFO("init success");
    Debug::Log("Wow");
}

// TODO: move this somewhere else
void Application::ProcessInput(){
    if (glfwGetKey(mWindow->GetWindow(), GLFW_KEY_W)){
        Renderer::GetMainCam()->Move(0.02f * Renderer::GetMainCam() ->  GetForward());
    }
    if (glfwGetKey(mWindow->GetWindow(), GLFW_KEY_S)){
        Renderer::GetMainCam()->Move(-0.02f * Renderer::GetMainCam()->  GetForward());
    }

    if (glfwGetKey(mWindow->GetWindow(), GLFW_KEY_D)){
        Renderer::GetMainCam()->Move(-0.02f * Renderer::GetMainCam()->  GetLeft());
    }
    if (glfwGetKey(mWindow->GetWindow(), GLFW_KEY_A)){
        Renderer::GetMainCam()->Move(0.02f * Renderer::GetMainCam() ->  GetLeft());
    }

    if (glfwGetKey(mWindow->GetWindow(), GLFW_KEY_E)){
        Renderer::GetMainCam()->Move(0.02f * Renderer::GetMainCam() -> GetUp());
    }
    if (glfwGetKey(mWindow->GetWindow(), GLFW_KEY_Q)){
        Renderer::GetMainCam()->Move(-0.02f * Renderer::GetMainCam()-> GetUp());
    }
}

void Application::Render(){

    // TODO: move this into renderer
    glViewport(0, 0, mWindow->width, mWindow->height);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);


    ui->BeginMenuBar();
    if (ImGui::BeginMenu("SEngine")) {
        if (ImGui::MenuItem("Quit")){
          glfwSetWindowShouldClose(mWindow->GetWindow(), true);
        }
        ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Windows")) {
        if (ImGui::MenuItem("Scene", NULL, &Application::sceneViewIsOpen)){
        }
        if (ImGui::MenuItem("Property", NULL, &Application::propertyViewIsOpen)){
        }
        if (ImGui::MenuItem("Debug", NULL, &Application::debugViewIsOpen)){
        }
        ImGui::EndMenu();
    }
    ui->EndMenuBar();
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