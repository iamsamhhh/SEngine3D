#pragma once
#include <glm/glm.hpp>
namespace SEngine{
struct Transform
{
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
};
}