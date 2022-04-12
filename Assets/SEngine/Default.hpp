#pragma once

#include "Material.hpp"
#include "Internal/RenderSystem.hpp"
#include "Internal/MoveSystem.hpp"
#include "Internal/LightSystem.hpp"
#include "Internal/TransformSystem.hpp"
#include "Internal/DebugView.hpp"
#include "Internal/PropertyView.hpp"
#include "Internal/SceneView.hpp"
#include "Internal/HierarchyView.hpp"
#include "GetEntitySystem.hpp"

namespace SEngine{
class Default
{
private:
    
public:
    static void Generate();
    static bool sceneIsOpen;
    static bool propertyIsOpen;
    static bool debugIsOpen;
    static bool hierarchyIsOpen;
    static Shader* defaultShader;
    static Material* defaultMat;

    static std::shared_ptr<SEngine_Internal::RenderSystem>      renderSystem;
    static std::shared_ptr<SEngine_Internal::MoveSystem>        moveSystem;
    static std::shared_ptr<SEngine_Internal::LightSystem>       lightSystem;
    static std::shared_ptr<SEngine_Internal::TransformSystem>   transformSystem;
    static std::shared_ptr<GetEntitySystem>                     getEntitySystem;
    static std::shared_ptr<SEngine_Internal::DebugView>         debugView;
    static std::shared_ptr<SEngine_Internal::PropertyView>      propertyView;
    static std::shared_ptr<SEngine_Internal::SceneView>         sceneView;
    static std::shared_ptr<SEngine_Internal::HierarchyView>     hierarchyView;
};
}