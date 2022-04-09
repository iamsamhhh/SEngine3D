#pragma once

#include "System.hpp"
#include "Transform.hpp"

using namespace SEngine;

namespace SEngine_Internal{
class TransformSystem : public SEngine::System
{
public:
	Transform* GetTransform(int index);
};
}