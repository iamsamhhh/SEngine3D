#pragma once
#include "Window.hpp"

class UI
{
public:

    UI() : mWindow(nullptr){};

    bool init(Window* window);

    void BeginMenuBar();

    void EndMenuBar();

    void post_render();

    void end();

private:

    Window* mWindow;
};