#include "Internal/Renderer.hpp"
#include "Internal/Engine.hpp"
#include "Internal/LoggingSystem.hpp"
#include "Internal/MainWindow.hpp"
#include "Internal/ViewBuilder.hpp"
#include "Default.hpp"
#include "Log.h"
#include "Debug.hpp"
namespace SEngine_Internal{
Engine* Engine::instance = nullptr;
Engine::~Engine()
{
    ui->end();
    Renderer::ShutDown();
    delete mWindow;
    glfwTerminate();
    LoggingSystem::ShutDown();
    app->OnAppEnd();
}

void RenderAll(){
    Engine::instance->Render();
}

void Engine::Init(){
    app = SEngine::CreatApplication();
    mWindow = new MainWindow(app->GetName(), 1080, 720, RenderAll);

    Renderer::Init();

    ui = new UI();
    ui->init(mWindow);

    LoggingSystem::Init();

    Default::Generate();
    app->OnAppStart();
}

void Engine::ProcessInput(){
    Renderer::GetMainCam()->ProcesssInput(mWindow->GetWindow());
}

void Engine::Render(){

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

void Engine::Loop(){
    while (!mWindow->WindowShouldClose())
    {
        ProcessInput();
        app->OnAppUpdate();
        Default::moveSystem->Update();
        Render();
    }
}
}