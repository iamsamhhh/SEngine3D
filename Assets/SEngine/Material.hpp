#pragma once

#include "Shader.h"
namespace SEngine{
#define MAX_VERTICIES_PER_MAT 5000
#define EOD 0.2468013579f

class Material
{
private:
    Shader shader;
public:
    Material();
    Material(Shader shader);
    Material(const char* vertexShaderPath, const char* fragmentShaderPath);
    Shader* Use();
    void SetMeshData(float* data);
    int count = 0;
    static int matCount;
    float vertices[MAX_VERTICIES_PER_MAT];
    ~Material();
};
}