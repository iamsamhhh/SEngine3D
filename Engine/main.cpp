#include "Engine.hpp"


int main()
{  
    Engine::instance = new Engine();
    
    Engine::instance->Init();
    Engine::instance->Loop();
    delete Engine::instance;

    return 0;
}
