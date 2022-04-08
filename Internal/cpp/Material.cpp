#include "Material.hpp"
namespace SEngine{

int Material::matCount = 0;
Material::Material(Shader* shader, SetVarInShaderFunc func) : shader(shader), func(func)
{
    matCount++;
}

Material::~Material(){}

Material::Material(const char* vertexShaderPath, const char* fragmentShaderPath, SetVarInShaderFunc func) : shader(new Shader(vertexShaderPath, fragmentShaderPath)), func(func)
{
    matCount++;
}

Material::Material(){}

void Material::SetMeshData(float* data){
    for (int j = 0; j < MAX_VERTICIES_PER_MAT; j++) {
        if (data[j] == EOD) {
            return;
        }
        else{
            vertices[count] = data[j];
            count++;
        }
    }
    std::cout << "Verticies number out of bound\n";
}

Shader* Material::Use(){
    shader->use();
    func(shader);
    return shader;
}
}