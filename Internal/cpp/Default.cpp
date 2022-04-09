#include "Default.hpp"
#include "Internal/PropertyView.hpp"
#include "Internal/SceneView.hpp"
#include "Internal/ViewBuilder.hpp"
#include "Internal/Renderer.hpp"
#include "Internal/DebugView.hpp"
#include "Transform.hpp"
#include "Velocity.hpp"
#include "MoveSystem.hpp"
#include "RenderSystem.hpp"
#include "Mesh.hpp"
#include "MeshRenderer.hpp"
#include "ECS_Manager.hpp"

using namespace SEngine_Internal;

namespace SEngine{
bool Default::sceneIsOpen    = true;
bool Default::propertyIsOpen = true;
bool Default::debugIsOpen    = true;
Material* Default::defaultMat = nullptr;
Shader* Default::defaultShader = nullptr;

std::shared_ptr<RenderSystem>   Default::renderSystem = nullptr;
std::shared_ptr<MoveSystem>     Default::moveSystem   = nullptr;
void WhiteFunc(Shader* shader){
    shader->setVec3("color", 0.3f, 0.9f, 0.5f);
    shader->setVec3("lightColor", 1.0f, 0.4f, 1.0f);
}
void Default::Generate(){

    // -----------------------------------Editor views init------------------------------------
    ViewBuilder::AddView(new PropertyView(&propertyIsOpen));
    ViewBuilder::AddView(new SceneView(&sceneIsOpen));
    ViewBuilder::AddView(new DebugView(&debugIsOpen));

    // ----------------------------------------ecs init----------------------------------------
    ECS_Manager::ecsManager->Init();
    ECS_Manager::ecsManager->RegisterComponent<Transform>();
    ECS_Manager::ecsManager->RegisterComponent<Velocity>();
    ECS_Manager::ecsManager->RegisterComponent<Mesh>();
    ECS_Manager::ecsManager->RegisterComponent<MeshRenderer>();

    moveSystem =    ECS_Manager::ecsManager->RegisterSystem<MoveSystem>();
    renderSystem =  ECS_Manager::ecsManager->RegisterSystem<RenderSystem>();

    Signature signature;

    signature.set(ECS_Manager::ecsManager->GetComponentType<Transform>());
    signature.set(ECS_Manager::ecsManager->GetComponentType<Velocity>());
	ECS_Manager::ecsManager->SetSystemSignature<MoveSystem>(signature);

    Signature signature2;
    
    signature2.set(ECS_Manager::ecsManager->GetComponentType<Transform>());
    signature2.set(ECS_Manager::ecsManager->GetComponentType<Mesh>());
    signature2.set(ECS_Manager::ecsManager->GetComponentType<MeshRenderer>());
	ECS_Manager::ecsManager->SetSystemSignature<RenderSystem>(signature2);

    defaultShader = new Shader(
        "/Users/chenyuxuansam/dev/SEngine3D/SEngine3D/Assets/Shaders/OneColor.vs",
        "/Users/chenyuxuansam/dev/SEngine3D/SEngine3D/Assets/Shaders/OneColor.fs"
    );
    Shader* lightShader = new Shader(
        "/Users/chenyuxuansam/dev/SEngine3D/SEngine3D/Assets/Shaders/OneColor.vs",
        "/Users/chenyuxuansam/dev/SEngine3D/SEngine3D/Assets/Shaders/Light.fs"
    );
    Material* mat = Renderer::CreateMaterial(defaultShader, WhiteFunc);
    Material* lightMat = Renderer::CreateMaterial(lightShader, nullptr);
    Entity light = ECS_Manager::ecsManager->CreateEntity();
    ECS_Manager::ecsManager->AddComponent(
		light,
		Transform{
			.position   = glm::vec3(1.2f, 1.0f, 2.0f),
            .heading    = 0,
            .pitch      = 0,
			.scale      = glm::vec3(0.2f)
	    }
    );
    ECS_Manager::ecsManager->AddComponent(
		light,
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
    ECS_Manager::ecsManager->AddComponent(
		light,
		MeshRenderer{
			.material = lightMat
	    }
    );
	Entity entity = ECS_Manager::ecsManager->CreateEntity();
	ECS_Manager::ecsManager->AddComponent(
		entity,
		Transform{
			.position   = glm::vec3(0, 0, 0),
            .heading    = 0,
            .pitch      = 0,
			.scale      = glm::vec3(1, 1, 1)
	    }
    );
    ECS_Manager::ecsManager->AddComponent(
        entity,
        Velocity{
            .velocity = glm::vec3(0, 0, 0.001f)
        }
    );
    ECS_Manager::ecsManager->AddComponent(
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
    ECS_Manager::ecsManager->AddComponent(
		entity,
		MeshRenderer{
			.material = mat
	    }
    );
	
    renderSystem->Init();
}
}