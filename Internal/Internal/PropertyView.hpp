#pragma once
#include "EditorView.hpp"
namespace SEngine_Internal{
class PropertyView : public EditorView
{
public:
    PropertyView(bool* IsOpen) : EditorView("Properties", IsOpen){}
    void OnRender() override;
};
}