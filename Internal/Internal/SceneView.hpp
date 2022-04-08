#pragma once
#include "EditorView.hpp"
namespace SEngine_Internal{
class SceneView : public EditorView
{
public:
    SceneView(bool* isOpen) : EditorView("Scene", isOpen){};
    void OnRender() override;
};
}