#include "Material.hpp"
namespace SEngine{
int Material::matCount = 0;
Material::Material(Shader shader)
{
    Material::shader = shader;
    matCount++;
}

Material::~Material(){}

Material::Material(const char* vertexShaderPath, const char* fragmentShaderPath){
    Material::shader = Shader(vertexShaderPath, fragmentShaderPath);
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
    shader.use();
    return &shader;
}
}