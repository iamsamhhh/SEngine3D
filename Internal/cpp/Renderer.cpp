#include "Internal/Renderer.hpp"
#include "Default.hpp"
namespace SEngine_Internal{
ImVec2 Renderer::mSceneSize = {1080, 720};
FrameBuffer* Renderer::mFramebuffer = nullptr;
Camera* Renderer::mMainCam = nullptr;

void Renderer::Init(){
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }
    
    mFramebuffer = new FrameBuffer();
    mFramebuffer->create_buffers(3840, 2160);
    mMainCam = new Camera();
    mMainCam->Move(glm::vec3(0, 0, -3.0f));
    mMainCam->Rotate(glm::vec3(0));
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
}

void Renderer::PreRender(Window* window){
    glViewport(0, 0, window->width, window->height);
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

Material* Renderer::CreateMaterial(SetVarInShaderFunc func){
    Material* mat = new Material(Default::defaultShader, func);
    return mat;
}

Material* Renderer::CreateMaterial(Shader* shader, SetVarInShaderFunc func){
    Material* mat = new Material(shader, func);
    return mat;
}

void Renderer::RegisterObject(Material* mat, int start, int end, Transform trans){
    int count = end-start;
    float* verticies;
    verticies = &(mat->vertices[start]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*count, verticies, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glm::mat4 model         = glm::rotate(glm::mat4(1.0f), trans.heading, glm::vec3(0, 1, 0));
    model                   = glm::rotate(model, trans.pitch, glm::rotate(glm::quat(glm::vec3(0,-trans.heading,0)), glm::vec3(1,0,0)));
    model                   = glm::translate(model, trans.position);
    model                   = glm::scale(model, trans.scale);
    glm::mat3 normalMat     = glm::transpose(glm::inverse(model));
    glm::mat4 projection    = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), (float)mSceneSize.x/(float)mSceneSize.y, 0.1f, 100.0f);
    Shader* shader = mat->Use();
    shader->setMat4("model", model);
    shader->setMat4("view", mMainCam->GetViewMat());
    shader->setMat4("projection", projection);
    shader->setVec3("lightColor", Default::lightSystem->GetColor(0));
    shader->setMat3("normalMat", normalMat);
    shader->setVec3("lightPos", Default::lightSystem->GetPos(0));
    shader->setVec3("viewPos", mMainCam->pos);
    glDrawArrays(GL_TRIANGLES, 0, count/3);
}

void Renderer::RenderObject(float ratio){
    // CONSOLE_LOG_INFO("in Renderer::Render");
    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    Default::renderSystem->Update();
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    // CONSOLE_LOG_INFO("after Renderer::Render loop");
}

Camera* Renderer::GetMainCam(){return mMainCam;}

void Renderer::Render(){
    mFramebuffer->bind();
    RenderObject((float)mSceneSize.x/(float)mSceneSize.y);
    mFramebuffer->unbind();
}

void Renderer::ShutDown(){
    mFramebuffer->delete_buffers();
}

uint32_t Renderer::GetTexture(){return mFramebuffer->get_texture();}
}