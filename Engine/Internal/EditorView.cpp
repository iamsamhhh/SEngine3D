#include "EditorView.hpp"

void EditorView::Render(){
    if (ImGui::Begin(title.c_str(), isOpen)){
        OnRender();
    }
    ImGui::End();
}
