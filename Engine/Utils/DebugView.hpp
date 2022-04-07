#include "../Internal/Window_and_UI/EditorView.hpp"

class DebugView : public EditorView{
    DebugView(bool* IsOpen) : EditorView("Properties", IsOpen){}
    void OnRender() override;
}