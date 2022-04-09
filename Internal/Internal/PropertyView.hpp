#pragma once
#include "EditorView.hpp"
#include "Transform.hpp"
#include "Default.hpp"

using namespace SEngine;

namespace SEngine_Internal{
class PropertyView : public EditorView
{
public:
    PropertyView(bool* IsOpen) : EditorView("Properties", IsOpen){
        trans = Default::transformSystem->GetTransform(0);
        pos[0]=trans->position.x;
        pos[1]=trans->position.y;
        pos[2]=trans->position.z;
        
    }
    void OnRender() override;
    float pos[3];
    Transform* trans;
};
}