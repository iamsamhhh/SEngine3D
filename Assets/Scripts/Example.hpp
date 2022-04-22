#pragma once

#include "Application.hpp"
using namespace SEngine;
class Example : public Application
{
public:
    Example() : Application("Example"){};
    void OnAppStart() override;
    void OnAppUpdate() override;
    void OnAppEnd() override;
};