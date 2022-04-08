#pragma once

#include "Material.hpp"
#include "RenderSystem.hpp"
#include "MoveSystem.hpp"

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
    static std::shared_ptr<RenderSystem> renderSystem;
    static std::shared_ptr<MoveSystem> moveSystem;
};
}