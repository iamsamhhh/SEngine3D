#include "ECS_Manager.hpp"
#include "MoveSystem.hpp"
#include "Transform.hpp"
#include "../../Log.h"

extern ECS_Manager ecsManager;

void MoveSystem::Init()
{
}

void MoveSystem::Update(float dt)
{
	for (auto const& entity : mEntities)
	{
		auto& transform = ecsManager.GetComponent<Transform>(entity);

		transform.position.x += dt;
        // CONSOLE_LOG_INFO("posx: {}", transform.position.x)
	}
}