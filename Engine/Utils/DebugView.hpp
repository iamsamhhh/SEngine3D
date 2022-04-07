#include "../Internal/Window_and_UI/EditorView.hpp"

class DebugView : public EditorView{
public:
    DebugView(bool* IsOpen) : EditorView("Debug", IsOpen){}
    void OnRender() override;
};