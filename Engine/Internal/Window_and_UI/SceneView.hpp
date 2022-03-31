#include "EditorView.hpp"

class SceneView : public EditorView
{
private:
    ImVec2 mSceneSize;
public:
    SceneView(bool* isOpen) : EditorView("Scene", isOpen){};
    void OnRender() override;
};