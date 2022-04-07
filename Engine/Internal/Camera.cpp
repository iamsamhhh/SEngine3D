#include "Camera.hpp"

void Camera::UpdateViewMat(){
    view  = glm::rotate(glm::mat4(1.0f), mHeading, glm::vec3(0, 1, 0));
    view  = glm::rotate(view, mPitch, glm::rotate(GetHeading(), glm::vec3(1, 0, 0)));
    view  = glm::translate(view, pos);
}

void Camera::Move(glm::vec3 moveAmount){
    pos += moveAmount;
    UpdateViewMat();
}

void Camera::Rotate(glm::vec3 rotateAmount){
    mHeading += rotateAmount.x;
    mPitch += rotateAmount.y;
    UpdateViewMat();
}

glm::quat Camera::GetHeading()
{
	return glm::quat(glm::vec3(0.0f, -mHeading, 0.0f));
}

glm::quat Camera::GetDir(){
    return glm::quat(glm::vec3(-mPitch, -mHeading, 0.0f));
}

glm::vec3 Camera::GetForward(){
    return glm::rotate(GetDir(), glm::vec3(0, 0, 1));
}

glm::vec3 Camera::GetUp(){
    return glm::rotate(GetDir(), glm::vec3(0, 1, 0));
}

glm::vec3 Camera::GetLeft(){
    return glm::rotate(GetDir(), glm::vec3(1, 0, 0));
}

glm::mat4 Camera::GetViewMat(){return view;}