#pragma once
#include "EditorView.hpp"

class PropertyView : public EditorView
{
public:
    PropertyView(bool* IsOpen) : EditorView("Properties", IsOpen){}
    void OnRender() override;
};