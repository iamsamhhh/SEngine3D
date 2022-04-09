#include "Internal/TransformSystem.hpp"
#include "ECS_Manager.hpp"

namespace SEngine_Internal{
    Transform* TransformSystem::GetTransform(int index){
        int i = 0;
        for (auto const& entity : mEntities){
            if (i == index)
                return &ECS_Manager::ecsManager->GetComponent<Transform>(entity);
        }
        return nullptr;
    }
}