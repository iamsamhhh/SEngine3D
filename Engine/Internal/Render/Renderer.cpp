#include "Renderer.hpp"

Material Renderer::materials[MAX_NUM_OF_MAT]{};
ImVec2 Renderer::mSceneSize = {1080, 720};
FrameBuffer* Renderer::mFramebuffer = nullptr;
Camera* Renderer::mMainCam = nullptr;
float vertices[] = {
    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,
    EOD
};

void Renderer::Init(){
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }
    materials[0] = Material("/Users/chenyuxuansam/dev/SEngine3D/SEngine3D/Engine/Shaders/OneColor.vs", "/Users/chenyuxuansam/dev/SEngine3D/SEngine3D/Engine/Shaders/OneColor.fs");
    materials[0].SetMeshData(vertices);
    mFramebuffer = new FrameBuffer();
    mFramebuffer->create_buffers(1920, 1080);
    mMainCam = new Camera();
    mMainCam->Move(glm::vec3(0, 0, -3.0f));
    mMainCam->Rotate(glm::vec3(0.001f));
}

void Renderer::RenderObject(float ratio){
    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    for (int i = 0; i < Material::matCount; i++) {
        glBufferData(GL_ARRAY_BUFFER, sizeof(materials[i].vertices), materials[i].vertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        Shader* shader = materials[i].Use();
        glm::mat4 model      = glm::mat4(1.0f);
        glm::mat4 view       = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        // model = glm::rotate(model, (float)0, glm::vec3(0.5f, 0.5f, 0.0f));
        view  = glm::rotate(view, glm::length(mMainCam->rot), glm::normalize(mMainCam->rot));
        view  = glm::translate(view, mMainCam->pos);
        projection = glm::perspective(glm::radians(45.0f), ratio, 0.1f, 100.0f);
        shader->setVec4("color", 1,1,1,1);
        shader->setMat4("model", model);
        shader->setMat4("view", view);
        shader->setMat4("projection", projection);
        // std::cout << materials[i].vertices << "\ncount " << materials[i].count/3 << "\n";
        glDrawArrays(GL_TRIANGLES, 0, materials[i].count/3);
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

Camera* Renderer::GetMainCam(){return mMainCam;}

void Renderer::Render(){
    mFramebuffer->bind();
    RenderObject((float)mSceneSize.x/(float)mSceneSize.y);
    mFramebuffer->unbind();
    ImGui::Begin("Scene");
    ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
    mSceneSize = viewportPanelSize;
    uint64_t textureID = mFramebuffer->get_texture();
    ImGui::Image(reinterpret_cast<void*>(textureID), viewportPanelSize, ImVec2(0, 1), ImVec2(1, 0));
    ImGui::End();
}

void Renderer::ShutDown(){
    mFramebuffer->delete_buffers();
}

uint32_t Renderer::GetTexture(){return mFramebuffer->get_texture();}