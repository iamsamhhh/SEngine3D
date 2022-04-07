#include "Application.hpp"
#include "Utils/Debug.hpp"
#include "Internal/Window_and_UI/MainWindow.hpp"
#include "Utils/Default.hpp"

Application* Application::instance = nullptr;
Application::~Application()
{
    ui->end();
    Renderer::ShutDown();
    delete mWindow;
    glfwTerminate();
    LoggingSystem::ShutDown();
}

void RenderAll(){
    Application::instance->Render();
}

void Application::Init(){

    mWindow = new MainWindow("SEngine", 1080, 720, RenderAll);

    Renderer::Init();

    ui = new UI();
    ui->init(mWindow);

    LoggingSystem::Init();

    Default::Generate();
}

void Application::ProcessInput(){
    Renderer::GetMainCam()->ProcesssInput(mWindow->GetWindow());
}

void Application::Render(){

    Renderer::PreRender(mWindow);

    ui->BeginMenuBar();
    if (ImGui::BeginMenu("SEngine")) {
        if (ImGui::MenuItem("Quit")){
          glfwSetWindowShouldClose(mWindow->GetWindow(), true);
        }
        ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Windows")) {
        if (ImGui::MenuItem("Scene", NULL,      &Default::sceneIsOpen)){
        }
        if (ImGui::MenuItem("Property", NULL,   &Default::propertyIsOpen)){
        }
        if (ImGui::MenuItem("Debug", NULL,      &Default::debugIsOpen)){
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