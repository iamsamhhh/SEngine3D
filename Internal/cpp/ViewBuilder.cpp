#include "Internal/ViewBuilder.hpp"

int ViewBuilder::count = 0;
EditorView* ViewBuilder::views[] = {};

void ViewBuilder::AddView(EditorView* view){
    views[count] = view;
    count++;
}

int ViewBuilder::GetCount(){return count;}