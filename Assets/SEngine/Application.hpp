#pragma once
#include <string>

namespace SEngine{
class Application
{
private:
std::string name;
public:
    Application(const char* name) {
        this->name = name;
    }
    virtual void OnAppStart() = 0;
    virtual void OnAppUpdate() = 0;
    virtual void OnAppEnd() = 0;
    const char* GetName(){return name.c_str();}
};
extern Application* CreatApplication();
}