#include "Application.hpp"


int main()
{  
    Application::instance = new Application();
    
    Application::instance->Init();
    Application::instance->Loop();
    Application::instance->ShutDown();

    return 0;
}
