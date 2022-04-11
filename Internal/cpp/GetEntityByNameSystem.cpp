#include "Name.hpp"
#include "GetEntitySystem.hpp"
#include "ECS_Manager.hpp"
#include "Debug.hpp"

namespace SEngine
{
Entity GetEntitySystem::Get(std::string name){
    for (auto const& entity : mEntities){
        if (ECS_Manager::ecsManager->GetComponent<Name>(entity).name == name)
            return entity;
    }
    Debug::Log("fail to find entity with name " + name);
    return -1;
}
}
