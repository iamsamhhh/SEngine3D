#include "../Core.hpp"

class UI
{
public:

    UI() : mWindow(nullptr){};

    bool init(Window* window);

    void pre_render();

    void post_render();

    void end();

private:

    Window* mWindow;
};