#pragma once

#include "Internal/EditorView.hpp"
#include "Types.h"

using namespace SEngine;

namespace SEngine_Internal{
class HierarchyView : public EditorView
{
private:
    Entity selectedEntity;
    bool hasEntitySelected;
public:
    HierarchyView(bool* isOpen) : EditorView("Hierarchy", isOpen){}
    bool HasEntitySelected();
    Entity GetSelectedEntity();
    void OnRender() override;
};
}