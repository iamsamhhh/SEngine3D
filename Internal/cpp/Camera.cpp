#include "Internal/Renderer.hpp"
#include "Internal/Camera.hpp"
#include "Internal/ViewBuilder.hpp"
#include "Log.h"

namespace SEngine_Internal{
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

void Camera::ProcesssInput(GLFWwindow* window){
    if (glfwGetKey(window, GLFW_KEY_W)){
        Renderer::GetMainCam()->Move(0.02f * Renderer::GetMainCam() ->  GetForward());
    }
    if (glfwGetKey(window, GLFW_KEY_S)){
        Renderer::GetMainCam()->Move(-0.02f * Renderer::GetMainCam()->  GetForward());
    }

    if (glfwGetKey(window, GLFW_KEY_D)){
        Renderer::GetMainCam()->Move(-0.02f * Renderer::GetMainCam()->  GetLeft());
    }
    if (glfwGetKey(window, GLFW_KEY_A)){
        Renderer::GetMainCam()->Move(0.02f * Renderer::GetMainCam() ->  GetLeft());
    }

    if (glfwGetKey(window, GLFW_KEY_E)){
        Renderer::GetMainCam()->Move(0.02f * Renderer::GetMainCam() -> GetUp());
    }
    if (glfwGetKey(window, GLFW_KEY_Q)){
        Renderer::GetMainCam()->Move(-0.02f * Renderer::GetMainCam()-> GetUp());
    }
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
}