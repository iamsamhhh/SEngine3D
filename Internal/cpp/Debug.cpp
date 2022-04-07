#include "Debug.hpp"
#include "Internal/DebugView.hpp"

void Debug::Log(std::string info){
    DebugView::AddLog(info);
}