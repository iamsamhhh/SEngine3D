#include "Debug.hpp"
#include "DebugView.hpp"

void Debug::Log(std::string info){
    DebugView::AddLog(info);
}