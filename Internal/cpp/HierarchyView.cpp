#include "Internal/HierarchyView.hpp"
#include "ECS_Manager.hpp"
#include "Default.hpp"
#include "Name.hpp"
#include "Internal/PropertyView.hpp"

namespace SEngine_Internal{
bool HierarchyView::HasEntitySelected(){
    return hasEntitySelected;
}
Entity HierarchyView::GetSelectedEntity(){
    return selectedEntity;
}
void HierarchyView::OnRender(){
    for (auto const& entity : Default::getEntitySystem->mEntities)
    {
        if (ImGui::Button(ECS_Manager::ecsManager->GetComponent<Name>(entity).name.c_str())){
            selectedEntity = entity;
            hasEntitySelected = true;
            Default::propertyView->SetSelectedEntity(true, selectedEntity);
        }
    }
    
}
}