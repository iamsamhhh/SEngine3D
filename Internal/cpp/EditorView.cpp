#include "Internal/EditorView.hpp"
namespace SEngine_Internal{
void EditorView::Render(){
    if (*isOpen){
        ImGui::Begin(title.c_str(), isOpen);
        OnRender();
        ImGui::End();
    }
    else {
        *isOpen = false;
    }
}
}