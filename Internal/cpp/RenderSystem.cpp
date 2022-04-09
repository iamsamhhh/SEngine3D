#include "ECS_Manager.hpp"
#include "Internal/RenderSystem.hpp"
#include "Transform.hpp"
#include "Mesh.hpp"
#include "MeshRenderer.hpp"
#include "Internal/Renderer.hpp"
#include "Log.h"

using namespace SEngine_Internal;
void RenderSystem::Init()
{
        for (auto const& entity : mEntities)
        {
                Mesh* mesh = &ECS_Manager::ecsManager->GetComponent<Mesh>(entity);
                MeshRenderer renderer = ECS_Manager::ecsManager->GetComponent<MeshRenderer>(entity);
                mesh->start = renderer.material->count;
                renderer.material->SetMeshData(mesh->verticies);
                mesh->end = renderer.material->count;
        }
}

void RenderSystem::Update()
{
	for (auto const& entity : mEntities)
	{
                Mesh mesh = ECS_Manager::ecsManager->GetComponent<Mesh>(entity);
                MeshRenderer renderer = ECS_Manager::ecsManager->GetComponent<MeshRenderer>(entity);
                Transform trans = ECS_Manager::ecsManager->GetComponent<Transform>(entity);
        
                Renderer::RegisterObject(renderer.material, mesh.start, mesh.end, trans);
	}
}