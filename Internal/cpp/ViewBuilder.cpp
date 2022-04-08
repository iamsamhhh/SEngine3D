#include "Internal/ViewBuilder.hpp"
namespace SEngine_Internal{
int ViewBuilder::count = 0;
EditorView* ViewBuilder::views[] = {};

void ViewBuilder::AddView(EditorView* view){
    views[count] = view;
    count++;
}

int ViewBuilder::GetCount(){return count;}
}