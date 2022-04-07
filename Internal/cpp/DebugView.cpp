#include "Internal/DebugView.hpp"

std::array<std::string, MAX_NUM_OF_LOG> DebugView::mLogs{};
int DebugView::count = 0;
void DebugView::AddLog(std::string log){
    if (count >= MAX_NUM_OF_LOG) return;
    DebugView::mLogs[DebugView::count] = log;
    count++;
}

void DebugView::OnRender(){
    if (ImGui::Button("add log")){AddLog("added log");}
    for (int i = 0; i < DebugView::count; i++)
    {
        ImGui::Text("%s", DebugView::mLogs[i].c_str());
    }
}