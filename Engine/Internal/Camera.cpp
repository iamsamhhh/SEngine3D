#include "Camera.hpp"

void Camera::Move(glm::vec3 moveAmount){
    pos += moveAmount;
    view  = glm::mat4(1.0f);
    view  = glm::rotate(view, mYaw, glm::vec3(0, 1, 0));
    view  = glm::rotate(view, mPitch, glm::rotate(GetDir(), glm::vec3(1, 0, 0)));
    view  = glm::translate(view, pos);
}

void Camera::Rotate(glm::vec3 rotateAmount){
    mYaw += rotateAmount.x;
    mPitch += rotateAmount.y;
    view  = glm::mat4(1.0f);
    view  = glm::rotate(view, mYaw, glm::vec3(0, 1, 0));
    view  = glm::rotate(view, mPitch, glm::rotate(GetDir(), glm::vec3(1, 0, 0)));
    view  = glm::translate(view, pos);
}

glm::quat Camera::GetDir()
{
	return glm::quat(glm::vec3(0.0f, -mYaw, 0.0f));
}

glm::vec3 Camera::GetForward(){
    return glm::rotate(GetDir(), glm::vec3(0, 0, 1));
}

glm::mat4 Camera::GetViewMat(){return view;}
glm::vec3 Camera::GetUp(){
    return glm::rotate(GetDir(), glm::vec3(0, 1, 0));
}