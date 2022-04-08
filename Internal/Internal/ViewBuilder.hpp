#pragma once
#include "EditorView.hpp"
namespace SEngine_Internal{
class ViewBuilder
{
private:
    static int count;
public:
    static void AddView(EditorView* view);
    static int GetCount();
    static EditorView* views[MAX_VIEW_NUM];
};
}