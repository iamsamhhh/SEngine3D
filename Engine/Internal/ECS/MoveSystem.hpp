#pragma once

#include "System.hpp"

class MoveSystem : public System
{
public:
	void Init();

	void Update(float dt);
};