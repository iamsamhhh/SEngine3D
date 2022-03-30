#pragma once
#include "EditorView.hpp"

class ViewBuilder
{
private:
    static EditorView::InitializingViewFunc initViewFuncs[MAX_VIEW_NUM];
    static int count;
public:
    static void AddViewInitializer(EditorView::InitializingViewFunc func);
    static void Build();
    static int GetCount();
    static EditorView* views[MAX_VIEW_NUM];
};