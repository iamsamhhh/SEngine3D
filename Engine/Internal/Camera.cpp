#include "Camera.hpp"

void Camera::Move(glm::vec3 moveAmount){
    pos += moveAmount;
}

void Camera::Rotate(glm::vec3 rotateAmount){
    rot += rotateAmount;
}

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