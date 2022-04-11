#include "Default.hpp"
#include <string>
#include "Internal/PropertyView.hpp"
#include "Internal/SceneView.hpp"
#include "Internal/ViewBuilder.hpp"
#include "Internal/Renderer.hpp"
#include "Internal/DebugView.hpp"
#include "Transform.hpp"
#include "Velocity.hpp"
#include "Mesh.hpp"
#include "Name.hpp"
#include "MeshRenderer.hpp"
#include "LightSource.hpp"
#include "ECS_Manager.hpp"


using namespace SEngine_Internal;

namespace SEngine{
bool Default::sceneIsOpen    = true;
bool Default::propertyIsOpen = true;
bool Default::debugIsOpen    = true;
Material* Default::defaultMat = nullptr;
Shader* Default::defaultShader = nullptr;

std::shared_ptr<RenderSystem>   Default::renderSystem   = nullptr;
std::shared_ptr<MoveSystem>     Default::moveSystem     = nullptr;
std::shared_ptr<LightSystem>    Default::lightSystem    = nullptr;
std::shared_ptr<TransformSystem>Default::transformSystem= nullptr;
std::shared_ptr<GetEntitySystem>Default::getEntitySystem= nullptr;

glm::vec3 lightPos(0.0f, 1.0f, 0.0f);
#define CUBE_VERTICIES {-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, EOD}


void Color(Shader* shader){
    shader->setVec3("objectColor", 0.3f, 0.9f, 0.5f);
}
void Default::Generate(){

    // ----------------------------------------ecs init----------------------------------------
    ECS_Manager::ecsManager->Init();
    ECS_Manager::ecsManager->RegisterComponent<Transform>();
    ECS_Manager::ecsManager->RegisterComponent<Velocity>();
    ECS_Manager::ecsManager->RegisterComponent<Mesh>();
    ECS_Manager::ecsManager->RegisterComponent<MeshRenderer>();
    ECS_Manager::ecsManager->RegisterComponent<LightSource>();
    ECS_Manager::ecsManager->RegisterComponent<Name>();

    moveSystem      = ECS_Manager::ecsManager->RegisterSystem<MoveSystem>();
    renderSystem    = ECS_Manager::ecsManager->RegisterSystem<RenderSystem>();
    lightSystem     = ECS_Manager::ecsManager->RegisterSystem<LightSystem>();
    transformSystem = ECS_Manager::ecsManager->RegisterSystem<TransformSystem>();
    getEntitySystem = ECS_Manager::ecsManager->RegisterSystem<GetEntitySystem>();

    Signature signature;

    signature.set(ECS_Manager::ecsManager->GetComponentType<Transform>());
    signature.set(ECS_Manager::ecsManager->GetComponentType<Velocity>());
	ECS_Manager::ecsManager->SetSystemSignature<MoveSystem>(signature);

    Signature signature2;
    
    signature2.set(ECS_Manager::ecsManager->GetComponentType<Transform>());
    signature2.set(ECS_Manager::ecsManager->GetComponentType<Mesh>());
    signature2.set(ECS_Manager::ecsManager->GetComponentType<MeshRenderer>());
	ECS_Manager::ecsManager->SetSystemSignature<RenderSystem>(signature2);

    Signature sig3;

    sig3.set(ECS_Manager::ecsManager->GetComponentType<Transform>());
    sig3.set(ECS_Manager::ecsManager->GetComponentType<LightSource>());
    ECS_Manager::ecsManager->SetSystemSignature<LightSystem>(sig3);

    Signature sig4;

    sig4.set(ECS_Manager::ecsManager->GetComponentType<Transform>());
    ECS_Manager::ecsManager->SetSystemSignature<TransformSystem>(sig4);

    Signature sigForGetEntitySystem;

    sigForGetEntitySystem.set(ECS_Manager::ecsManager->GetComponentType<Name>());
    ECS_Manager::ecsManager->SetSystemSignature<GetEntitySystem>(sigForGetEntitySystem);

    defaultShader = new Shader(
        "/Users/chenyuxuansam/dev/SEngine3D/SEngine3D/Assets/Shaders/OneColor.vs",
        "/Users/chenyuxuansam/dev/SEngine3D/SEngine3D/Assets/Shaders/OneColor.fs"
    );
    Shader* lightShader = new Shader(
        "/Users/chenyuxuansam/dev/SEngine3D/SEngine3D/Assets/Shaders/Light.vs",
        "/Users/chenyuxuansam/dev/SEngine3D/SEngine3D/Assets/Shaders/Light.fs"
    );
    Material* mat = Renderer::CreateMaterial(defaultShader, Color);
    Material* lightMat = Renderer::CreateMaterial(lightShader, nullptr);
    Entity light = ECS_Manager::ecsManager->CreateEntity("light");

    ECS_Manager::ecsManager->AddComponent(
		light,
		Transform{
			.position   = lightPos,
            .heading    = 0,
            .pitch      = 0,
			.scale      = glm::vec3(0.2f)
	    }
    );
    ECS_Manager::ecsManager->AddComponent(
		light,
		Mesh{
			.verticies = CUBE_VERTICIES
	    }
    );
    ECS_Manager::ecsManager->AddComponent(
		light,
		LightSource{
			.lightColor = glm::vec3(1.0f, 1.0f, 1.0f) * 0.8f
	    }
    );
    ECS_Manager::ecsManager->AddComponent(
		light,
		MeshRenderer{
			.material = lightMat
	    }
    );

  std::vector<Entity> entities(3);
  for (auto& entity : entities) {
    entity = ECS_Manager::ecsManager->CreateEntity();

	  ECS_Manager::ecsManager->AddComponent(
		entity,
		Transform{
			.position   = glm::vec3((entity-1)*1.5, 0, 0),
      .heading    = 0,
      .pitch      = 0,
			.scale      = glm::vec3(1, 1, 1)
	    }
    );

    // ECS_Manager::ecsManager->AddComponent(
    //     entity,
    //     Velocity{
    //         .velocity = glm::vec3(0, 0, 0.01f)
    //     }
    // );

    ECS_Manager::ecsManager->AddComponent(
		entity,
		Mesh{
			.verticies = CUBE_VERTICIES
	    }
    );

    ECS_Manager::ecsManager->AddComponent(
		entity,
		MeshRenderer{
			.material = mat
	    }
    );

  }

    renderSystem->Init();

    // -----------------------------------Editor views init------------------------------------
    ViewBuilder::AddView(new PropertyView(&propertyIsOpen));
    ViewBuilder::AddView(new SceneView(&sceneIsOpen));
    ViewBuilder::AddView(new DebugView(&debugIsOpen));
}
}