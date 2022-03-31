#include "Application.hpp"


int main()
{  
    Application::instance = new Application();
    
    Application::instance->Init();
    Application::instance->Loop();
    delete Application::instance;

    return 0;
}
