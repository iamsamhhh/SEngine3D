#pragma once

#include "Shader.h"
#include <array>
namespace SEngine{

#define MAX_VERTICIES_PER_MAT 5000
#define EOD 0.2468013579f

typedef void (* SetVarInShaderFunc)(Shader* shader);

class Material
{
private:
    Shader* shader;
    SetVarInShaderFunc func;
public:
    Material();
    Material(Shader* shader, SetVarInShaderFunc func);
    Material(const char* vertexShaderPath, const char* fragmentShaderPath, SetVarInShaderFunc func);
    Shader* Use();
    void SetMeshData(float* data);
    int count = 0;
    static int matCount;
    float vertices[MAX_VERTICIES_PER_MAT];
    ~Material();
};
}