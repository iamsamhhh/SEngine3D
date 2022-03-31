#include "SceneView.hpp"
#include "../Render/Renderer.hpp"
void SceneView::OnRender(){
    ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
    mSceneSize = viewportPanelSize;
    uint64_t textureID = Renderer::GetTexture();
    ImGui::Image(reinterpret_cast<void*>(textureID), viewportPanelSize, ImVec2(0, 1), ImVec2(1, 0));
    CONSOLE_LOG_INFO("scene view on render");
}