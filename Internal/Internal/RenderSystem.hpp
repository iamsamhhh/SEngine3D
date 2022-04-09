#pragma once

#include "System.hpp"
namespace SEngine_Internal{
class RenderSystem : public SEngine::System
{
public:
	void Init();

	void Update();
};
}