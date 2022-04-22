#include "Example.hpp"
#include "Debug.hpp"

void Example::OnAppStart(){
    Debug::Log("App start successfully");
}

void Example::OnAppUpdate(){

}

void Example::OnAppEnd(){

}

Application* SEngine::CreatApplication(){
    return new Example();
}