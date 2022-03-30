#include "ViewBuilder.hpp"

int ViewBuilder::count = 0;
EditorView::InitializingViewFunc ViewBuilder::initViewFuncs[] = {};
EditorView* ViewBuilder::views[] = {};

void ViewBuilder::Build(){
    for (int i = 0; i < count; i++)
    {
        views[i] = initViewFuncs[i]();
    }
}

void ViewBuilder::AddViewInitializer(EditorView::InitializingViewFunc func){
    initViewFuncs[count] = func;
    count++;
}

int ViewBuilder::GetCount(){return count;}