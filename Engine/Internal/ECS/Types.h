#pragma once

#include <queue>
#include <array>
#include <bitset>
#include <cstdint>

// A simple type alias
using Entity = std::uint32_t;

// Used to define the size of arrays later on
#define MAX_ENTITIES = 5000;

// A simple type alias
using ComponentType = std::uint8_t;

// Used to define the size of arrays later on
#define MAX_COMPONENTS = 32;

// A simple type alias
using Signature = std::bitset<MAX_COMPONENTS>;