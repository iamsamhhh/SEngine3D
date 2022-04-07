#include "../Camera.hpp"

#define MAX_NUM_OF_MAT 100

class Renderer{
    private:
    static Material* materials[MAX_NUM_OF_MAT];
    static FrameBuffer* mFramebuffer;
    static Camera* mMainCam;
    public:
    static ImVec2 mSceneSize;
    static void Init();
    static void RenderObject(float ratio);
    static void Render();
    static Material* CreateMaterial(const char* vertexShaderPath, const char* fragmentShaderPath);
    static void ShutDown();
    static Camera* GetMainCam();
    static uint32_t GetTexture();
};