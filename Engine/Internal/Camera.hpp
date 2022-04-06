#pragma once
#include "Window_and_UI/ViewBuilder.hpp"
#include <glm/gtx/quaternion.hpp>

class Camera
{
private:
    glm::mat4 view;
    float mYaw, mPitch;
public:
    glm::vec3 pos;
    glm::vec3 rot;
    glm::vec3 forward;
    Camera() : view(glm::mat4(1)), pos(glm::vec3(0)), rot(glm::vec3(0)){}
    void Rotate(glm::vec3 rotateAmount);
    void Move(glm::vec3 moveAmount);
    glm::quat GetDir();
    glm::mat4 GetViewMat();
    glm::vec3 GetUp();
    glm::vec3 GetForward();
};