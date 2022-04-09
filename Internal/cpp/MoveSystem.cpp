#include "ECS_Manager.hpp"
#include "Internal/MoveSystem.hpp"
#include "Transform.hpp"
#include "Velocity.hpp"
#include "Log.h"

namespace SEngine_Internal{

void MoveSystem::Update()
{
	for (auto const& entity : mEntities)
	{
		Transform* transform = &ECS_Manager::ecsManager->GetComponent<Transform>(entity);
		Velocity* velo = &ECS_Manager::ecsManager->GetComponent<Velocity>(entity);

		transform->position += velo->velocity;
	}
}
}