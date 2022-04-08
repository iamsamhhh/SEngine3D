#pragma once

#include "System.hpp"
namespace SEngine{
class MoveSystem : public System
{
public:
	void Init();

	void Update(float dt);
};
}