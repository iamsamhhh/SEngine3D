#include "ECS_Manager.hpp"
#include "RenderSystem.hpp"
// #include "Transform.hpp"
#include "Mesh.hpp"
#include "MeshRenderer.hpp"
// #include "../Render/Renderer.hpp"
#include "../../Log.h"

extern ECS_Manager ecsManager;

void RenderSystem::Init()
{
    for (auto const& entity : mEntities)
	{
		// Transform transform = ecsManager.GetComponent<Transform>(entity);
        Mesh mesh = ecsManager.GetComponent<Mesh>(entity);
        MeshRenderer renderer = ecsManager.GetComponent<MeshRenderer>(entity);

        renderer.material->SetMeshData(mesh.verticies);
	}
}

void RenderSystem::Update()
{
	
}