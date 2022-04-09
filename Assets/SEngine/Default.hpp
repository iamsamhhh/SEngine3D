#pragma once

#include "Material.hpp"
#include "Internal/RenderSystem.hpp"
#include "Internal/MoveSystem.hpp"
#include "Internal/LightSystem.hpp"

namespace SEngine{
class Default
{
private:
    
public:
    static void Generate();
    static bool sceneIsOpen;
    static bool propertyIsOpen;
    static bool debugIsOpen;
    static Shader* defaultShader;
    static Material* defaultMat;
    static std::shared_ptr<SEngine_Internal::RenderSystem>  renderSystem;
    static std::shared_ptr<SEngine_Internal::MoveSystem>    moveSystem;
    static std::shared_ptr<SEngine_Internal::LightSystem>   lightSystem;
};
}