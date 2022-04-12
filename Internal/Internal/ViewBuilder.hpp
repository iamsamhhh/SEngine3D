#pragma once
#include "EditorView.hpp"
namespace SEngine_Internal{
class ViewBuilder
{
private:
    static int count;
public:
    static void AddView(std::shared_ptr<EditorView> view);
    static int GetCount();
    static std::shared_ptr<EditorView> views[MAX_VIEW_NUM];
};
}