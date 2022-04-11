#include "Internal/PropertyView.hpp"

namespace SEngine_Internal{

void PropertyView::OnRender(){
    ImGui::Text("Entity num: %i, name: %s", Default::getEntitySystem->Get("light"), "light");
    ImGui::InputFloat3("pos", pos, "%.2f");
    trans->position.x = pos[0];
    trans->position.y = pos[1];
    trans->position.z = pos[2];
}
}