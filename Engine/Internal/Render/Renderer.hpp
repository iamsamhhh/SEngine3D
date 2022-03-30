#include "../Camera.hpp"

#define MAX_NUM_OF_MAT 100

class Renderer{
    private:
    static Material materials[MAX_NUM_OF_MAT];
    static FrameBuffer* mFramebuffer;
    static ImVec2 mSceneSize;
    static Camera* mMainCam;
    public:
    static void Init();
    static void RenderObject(float ratio);
    static void Render();
    static void ShutDown();
    static Camera* GetMainCam();
    static uint32_t GetTexture();
};