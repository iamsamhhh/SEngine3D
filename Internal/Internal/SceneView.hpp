#pragma once
#include "EditorView.hpp"

class SceneView : public EditorView
{
public:
    SceneView(bool* isOpen) : EditorView("Scene", isOpen){};
    void OnRender() override;
};