#pragma once

#include "EditorView.hpp"
#include "Transform.hpp"
#include "Types.h"

using namespace SEngine;

namespace SEngine_Internal{
class PropertyView : public EditorView
{
private:
    bool hasEntitySelected = false;
    Entity selectedEntity;
public:
    PropertyView(bool* IsOpen) : EditorView("Properties", IsOpen){
        SetSelectedEntity(false);
    }
    void OnRender() override;
    bool SetSelectedEntity(bool hasEntitySelected, Entity entity = 0);
};
}