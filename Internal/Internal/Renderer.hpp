#pragma once
#include "Material.hpp"
#include "FrameBuffer.hpp"
#include "Camera.hpp"
#include "Window.hpp"
#include "imgui/imgui.h"

#define MAX_NUM_OF_MAT 100

class Renderer{
    private:
    static Material* materials[MAX_NUM_OF_MAT];
    static FrameBuffer* mFramebuffer;
    static Camera* mMainCam;
    public:
    static void PreRender(Window* window);
    static void Init();
    static void RenderObject(float ratio);
    static void Render();
    static void ShutDown();
    static Material* CreateMaterial(const char* vertexShaderPath, const char* fragmentShaderPath);
    static Camera* GetMainCam();
    static uint32_t GetTexture();
    static ImVec2 mSceneSize;
};