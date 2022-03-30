#pragma once
#include "ViewBuilder.hpp"

class Camera
{
private:
    // float mPitch, mYaw;
    // const glm::vec3 cRight = { 1.0f, 0.0f, 0.0f };
	// const glm::vec3 cUp = { 0.0f, 1.0f, 0.0f };
	// const glm::vec3 cForward = { 0.0f, 0.0f, -1.0f };
public:
    glm::vec3 pos;
    glm::vec3 rot;
    Camera() : pos(glm::vec3(0)), rot(glm::vec3(0)){}
    void Rotate(glm::vec3 rotateAmount);
    void Move(glm::vec3 moveAmount);
    // glm::vec3 get_up();
    // glm::vec3 get_right();
    // glm::vec3 get_forward();
    // glm::quat get_direction();
};