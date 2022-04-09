#include "Internal/LightSystem.hpp"
#include "LightSource.hpp"
#include "Transform.hpp"
#include "ECS_Manager.hpp"
using namespace SEngine;

namespace SEngine_Internal{
glm::vec3 LightSystem::GetPos(int index){
    int i = 0;
    for (auto const& entity : mEntities){
        if (i == index)
            return ECS_Manager::ecsManager->GetComponent<Transform>(entity).position;
    }
    return glm::vec3(0);
}
glm::vec3 LightSystem::GetColor(int index){
    int i = 0;
    for (auto const& entity : mEntities){
        if (i == index)
            return ECS_Manager::ecsManager->GetComponent<LightSource>(entity).lightColor;
    }
    return glm::vec3(1);
}
}