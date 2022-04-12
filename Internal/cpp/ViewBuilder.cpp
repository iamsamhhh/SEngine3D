#include "Internal/ViewBuilder.hpp"
namespace SEngine_Internal{
int ViewBuilder::count = 0;
std::shared_ptr<EditorView> ViewBuilder::views[] = {};

void ViewBuilder::AddView(std::shared_ptr<EditorView> view){
    views[count] = view;
    count++;
}

int ViewBuilder::GetCount(){return count;}
}