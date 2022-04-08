#include "Internal/Engine.hpp"

using namespace SEngine_Internal;

int main()
{  
    Engine::instance = new Engine();
    
    Engine::instance->Init();
    Engine::instance->Loop();
    delete Engine::instance;

    return 0;
}
