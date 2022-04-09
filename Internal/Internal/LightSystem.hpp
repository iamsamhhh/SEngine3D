#pragma once

#include <glm/glm.hpp>
#include "System.hpp"

namespace SEngine_Internal{
class LightSystem : public SEngine::System
{
public:
	glm::vec3 GetPos(int index);
    glm::vec3 GetColor(int index);
};
}