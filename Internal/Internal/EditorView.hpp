#pragma once

#define MAX_VIEW_NUM 20

#include <string>
#include <imgui/imgui.h>

class EditorView
{
public:
    typedef EditorView* (* InitializingViewFunc)();
    EditorView() : title(nullptr), isOpen(nullptr){}
    EditorView(std::string title, bool* isOpen) : title(title), isOpen(isOpen){}
    virtual void OnRender() = 0;
    void Render();
    bool IsOpen(){return *isOpen;}
    std::string title;
private:
    bool* isOpen;
};