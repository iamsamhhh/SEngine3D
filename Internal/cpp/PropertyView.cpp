#include "Internal/PropertyView.hpp"
#include "ECS_Manager.hpp"
#include "Default.hpp"

namespace SEngine_Internal{

void PropertyView::OnRender(){
    if (!hasEntitySelected)
        return;
    Signature sig = ECS_Manager::ecsManager->GetEntitySignature(selectedEntity);
    ImGui::Text("Name: %s", ECS_Manager::ecsManager->GetComponent<Name>(selectedEntity).name.c_str());
    for (int i = 0; i < sig.count(); i++)
    {
        if (sig[i] == 1)
        {
            ImGui::Text("Component %i: %s", i, ECS_Manager::ecsManager->GetTypeName(i));
        }
    }
}

bool PropertyView::SetSelectedEntity(bool hasEntitySelected, Entity entity){
    this->hasEntitySelected = hasEntitySelected;
    if (!hasEntitySelected)
        return false;
    if (!Default::getEntitySystem->Exist(entity))
        return false;
    this->selectedEntity = entity;
    return true;
}
}