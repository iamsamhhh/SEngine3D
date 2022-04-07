#include "Internal/Default.hpp"
#include "Internal/PropertyView.hpp"
#include "Internal/SceneView.hpp"
#include "Internal/ViewBuilder.hpp"
#include "Internal/Renderer.hpp"
#include "Internal/DebugView.hpp"
#include "Transform.hpp"
#include "MoveSystem.hpp"
#include "RenderSystem.hpp"
#include "Mesh.hpp"
#include "MeshRenderer.hpp"
#include "ECS_Manager.hpp"


bool Default::sceneIsOpen    = true;
bool Default::propertyIsOpen = true;
bool Default::debugIsOpen    = true;

std::shared_ptr<RenderSystem> renderSystem;
std::shared_ptr<MoveSystem> moveSystem;
void Default::Generate(){

    // -----------------------------------Editor views init------------------------------------
    ViewBuilder::AddView(new PropertyView(&propertyIsOpen));
    ViewBuilder::AddView(new SceneView(&sceneIsOpen));
    ViewBuilder::AddView(new DebugView(&debugIsOpen));

    // ----------------------------------------ecs init----------------------------------------
    ECS_Manager::ecsManager->Init();
    ECS_Manager::ecsManager->RegisterComponent<Transform>();
    ECS_Manager::ecsManager->RegisterComponent<Mesh>();
    ECS_Manager::ecsManager->RegisterComponent<MeshRenderer>();

    moveSystem =    ECS_Manager::ecsManager->RegisterSystem<MoveSystem>();
    renderSystem =  ECS_Manager::ecsManager->RegisterSystem<RenderSystem>();

    Signature signature;

    signature.set(ECS_Manager::ecsManager->GetComponentType<Transform>());
	ECS_Manager::ecsManager->SetSystemSignature<MoveSystem>(signature);

    Signature signature2;

    signature2.set(ECS_Manager::ecsManager->GetComponentType<Mesh>());
    signature2.set(ECS_Manager::ecsManager->GetComponentType<MeshRenderer>());
	ECS_Manager::ecsManager->SetSystemSignature<RenderSystem>(signature2);

    std::vector<Entity> entities(5);
    Material* mat = Renderer::CreateMaterial(
        "/Users/chenyuxuansam/dev/SEngine3D/SEngine3D/Assets/Shaders/OneColor.vs",
        "/Users/chenyuxuansam/dev/SEngine3D/SEngine3D/Assets/Shaders/OneColor.fs"
    );
    for (auto& entity : entities)
	{
		entity = ECS_Manager::ecsManager->CreateEntity();

		ECS_Manager::ecsManager->AddComponent(
			entity,
			Transform{
				.position   = glm::vec3(0, 0, 0),
				.rotation   = glm::vec3(0, 0, 0),
				.scale      = glm::vec3(1, 1, 1)
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
	}
    renderSystem->Init();
}