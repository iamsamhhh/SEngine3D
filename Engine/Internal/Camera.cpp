#include "Camera.hpp"

void Camera::Move(glm::vec3 moveAmount){
    view = glm::mat4(1.0f);
    view  = glm::rotate(view, glm::length(rot), glm::normalize(rot));
    view  = glm::translate(view, pos);
    pos += moveAmount;
}

void Camera::Rotate(glm::vec3 rotateAmount){
    rot += rotateAmount;
    view = glm::mat4(1.0f);
    view  = glm::rotate(view, glm::length(rot), glm::normalize(rot));
    view  = glm::translate(view, pos);
    // std::cout << "x: " << rot.x << "    y: " << rot.y << "    z: " << rot.z << "\n";
}

glm::mat4 Camera::GetViewMat(){return view;}

// glm::vec3 Camera::get_up()
// {
// 	return glm::rotate(get_direction(), cUp);
// }
// glm::vec3 Camera::get_right()
// {
// 	return glm::rotate(get_direction(), cRight);
// }
// glm::vec3 Camera::get_forward()
// {
// 	return glm::rotate(get_direction(), cForward);
// }
// glm::quat Camera::get_direction()
// {
// 	return glm::quat(glm::vec3(-mPitch, -mYaw, 0.0f));
// }