#pragma once

#include "EditorView.hpp"
#include <string.h>
#include <array>

#define MAX_NUM_OF_LOG 10000

class DebugView : public EditorView{
private:
    static std::array<std::string, MAX_NUM_OF_LOG> mLogs;
    static int count;
public:
    static void AddLog(std::string log);
    DebugView(bool* IsOpen) : EditorView("Debug", IsOpen){}
    void OnRender() override;
};