#pragma once
#include <glm/glm.hpp>
namespace SEngine{
struct Transform
{
	glm::vec3 position;
	float heading, pitch;
	glm::vec3 scale;
};
}