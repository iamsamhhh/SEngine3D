#include "ECS_Manager.hpp"
#include "MoveSystem.hpp"
#include "Transform.hpp"
#include "Velocity.hpp"
#include "Log.h"

extern ECS_Manager ecsManager;

void MoveSystem::Init()
{
}

void MoveSystem::Update(float dt)
{
	for (auto const& entity : mEntities)
	{
		Transform* transform = &ECS_Manager::ecsManager->GetComponent<Transform>(entity);
		Velocity* velo = &ECS_Manager::ecsManager->GetComponent<Velocity>(entity);

		transform->position += velo->velocity;
	}
}