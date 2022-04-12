#include "Name.hpp"
#include "GetEntitySystem.hpp"
#include "ECS_Manager.hpp"
#include "Debug.hpp"
#include <cassert>

namespace SEngine
{
Entity GetEntitySystem::Get(std::string name){
    
    for (auto const& entity : mEntities){
        if (ECS_Manager::ecsManager->GetComponent<Name>(entity).name == name)
            return entity;
    }
    
    assert(false && ("Entity with name: " + name + "doesn't exist!").c_str());
    
    return -1;
}

bool GetEntitySystem::Exist(std::string name){
    for (auto const& entity : mEntities){
        if (ECS_Manager::ecsManager->GetComponent<Name>(entity).name == name)
            return true;
    }
    return false;
}
bool GetEntitySystem::Exist(Entity id){
    for (auto const& entity : mEntities){
        if (entity == id)
            return true;
    }

    return false;
}
}
