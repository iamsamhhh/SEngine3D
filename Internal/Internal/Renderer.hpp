#pragma once
#include "Material.hpp"
#include "FrameBuffer.hpp"
#include "Camera.hpp"
#include "Window.hpp"
#include "imgui/imgui.h"
#include "Transform.hpp"

using namespace SEngine;
namespace SEngine_Internal{
#define MAX_NUM_OF_MAT 100

class Renderer{
    private:
    static Material* materials[MAX_NUM_OF_MAT];
    static FrameBuffer* mFramebuffer;
    static Camera* mMainCam;
    static void RenderObject(float ratio);
    public:
    static void PreRender(Window* window);
    static void Init();
    static void Render();
    static void RegisterObject(Material* mat, int start, int end, Transform trans);
    static void ShutDown();
    static Material* CreateMaterial(SetVarInShaderFunc func);
    static Material* CreateMaterial(Shader* shader, SetVarInShaderFunc func);
    static Camera* GetMainCam();
    static uint32_t GetTexture();
    static ImVec2 mSceneSize;
};
}