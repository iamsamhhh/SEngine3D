#include "Application.hpp"
#include "Internal/ECS/Transform.hpp"
#include "Internal/ECS/MoveSystem.hpp"
#include "Internal/ECS/RenderSystem.hpp"
#include "Internal/ECS/Mesh.hpp"
#include "Internal/ECS/MeshRenderer.hpp"

bool Application::propertyViewIsOpen = true;
bool Application::sceneViewIsOpen = true;
ECS_Manager ecsManager;

Application* Application::instance = nullptr;
Application::~Application()
{
    ui->end();
    Renderer::ShutDown();
    delete mWindow;
    glfwTerminate();
    LoggingSystem::ShutDown();
}

void Application::frameBufferCallback(GLFWwindow* window, int width, int height){
    Window* fWindow = (Window*)glfwGetWindowUserPointer(window);
    fWindow->height = height;
    fWindow->width = width;
    instance->Render();
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

std::shared_ptr<MoveSystem> moveSystem;
std::shared_ptr<RenderSystem> renderSystem;
void Application::Init(){
    mWindow = new Window("SEngine", 1080, 720, frameBufferCallback);
    glfwSetWindowUserPointer(mWindow->GetWindow(), mWindow);
    glfwSetCursorPosCallback(mWindow->GetWindow(), CursorPosCallback);
    Renderer::Init();
    ui = new UI();
    ui->init(mWindow);
    ViewBuilder::AddView((EditorView* )(new PropertyView(&Application::propertyViewIsOpen)));
    ViewBuilder::AddView((EditorView* )(new SceneView(&Application::sceneViewIsOpen)));
    LoggingSystem::Init();
    CONSOLE_LOG_INFO("Logging system initialized!");
    ecsManager.Init();
    ecsManager.RegisterComponent<Transform>();
    ecsManager.RegisterComponent<Mesh>();
    ecsManager.RegisterComponent<MeshRenderer>();

    moveSystem = ecsManager.RegisterSystem<MoveSystem>();
    renderSystem = ecsManager.RegisterSystem<RenderSystem>();

    Signature signature;

    signature.set(ecsManager.GetComponentType<Transform>());
	ecsManager.SetSystemSignature<MoveSystem>(signature);

    Signature signature2;

    signature2.set(ecsManager.GetComponentType<Mesh>());
    signature2.set(ecsManager.GetComponentType<MeshRenderer>());
	ecsManager.SetSystemSignature<RenderSystem>(signature2);

	std::vector<Entity> entities(5);
    Material* mat = Renderer::CreateMaterial("/Users/chenyuxuansam/dev/SEngine3D/SEngine3D/Engine/Shaders/OneColor.vs", "/Users/chenyuxuansam/dev/SEngine3D/SEngine3D/Engine/Shaders/OneColor.fs");
    for (auto& entity : entities)
	{
		entity = ecsManager.CreateEntity();

		ecsManager.AddComponent(
			entity,
			Transform{
				.position   = glm::vec3(0, 0, 0),
				.rotation   = glm::vec3(0, 0, 0),
				.scale      = glm::vec3(1, 1, 1)
		    }
        );

        ecsManager.AddComponent(
			entity,
			Mesh{
				.verticies = {
                    -0.5f, -0.5f, -0.5f,
                     0.5f, -0.5f, -0.5f,
                     0.5f,  0.5f, -0.5f,
                     0.5f,  0.5f, -0.5f,
                    -0.5f,  0.5f, -0.5f,
                    -0.5f, -0.5f, -0.5f,
                    -0.5f, -0.5f,  0.5f,
                     0.5f, -0.5f,  0.5f,
                     0.5f,  0.5f,  0.5f,
                     0.5f,  0.5f,  0.5f,
                    -0.5f,  0.5f,  0.5f,
                    -0.5f, -0.5f,  0.5f,
                    -0.5f,  0.5f,  0.5f,
                    -0.5f,  0.5f, -0.5f,
                    -0.5f, -0.5f, -0.5f,
                    -0.5f, -0.5f, -0.5f,
                    -0.5f, -0.5f,  0.5f,
                    -0.5f,  0.5f,  0.5f,
                     0.5f,  0.5f,  0.5f,
                     0.5f,  0.5f, -0.5f,
                     0.5f, -0.5f, -0.5f,
                     0.5f, -0.5f, -0.5f,
                     0.5f, -0.5f,  0.5f,
                     0.5f,  0.5f,  0.5f,
                    -0.5f, -0.5f, -0.5f,
                     0.5f, -0.5f, -0.5f,
                     0.5f, -0.5f,  0.5f,
                     0.5f, -0.5f,  0.5f,
                    -0.5f, -0.5f,  0.5f,
                    -0.5f, -0.5f, -0.5f,
                    -0.5f,  0.5f, -0.5f,
                     0.5f,  0.5f, -0.5f,
                     0.5f,  0.5f,  0.5f,
                     0.5f,  0.5f,  0.5f,
                    -0.5f,  0.5f,  0.5f,
                    -0.5f,  0.5f, -0.5f,
                    EOD
                }
		    }
        );

        ecsManager.AddComponent(
			entity,
			MeshRenderer{
				.material = mat
		    }
        );
	}
    renderSystem->Init();
    CONSOLE_LOG_INFO("init success");
}


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
        moveSystem->Update(0.01f);
    }
}