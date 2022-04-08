#include "Debug.hpp"
#include "Internal/DebugView.hpp"
namespace SEngine{
void Debug::Log(std::string info){
    SEngine_Internal::DebugView::AddLog(info);
}
}