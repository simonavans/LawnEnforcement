#include "FirstPersonCamera.h"

#include <GLFW/glfw3.h>
#include <glm/ext/matrix_transform.hpp>

FirstPersonCamera::FirstPersonCamera(GLFWwindow* window)
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	if (glfwRawMouseMotionSupported())
		glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
}

void FirstPersonCamera::update(GLFWwindow* window, const float deltaTime)
{
	double x, y;
	glfwGetCursorPos(window, &x, &y);

	static double lastX = x;
	static double lastY = y;

	rotation_.x -= static_cast<float>(lastY - y) / 100.0f;
	rotation_.y -= static_cast<float>(lastX - x) / 100.0f;

	lastX = x;
	lastY = y;

	constexpr float fac = 2.0f;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		move(0, fac * deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		move(180, fac * deltaTime);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		move(90, fac * deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		move(-90, fac * deltaTime);
}

glm::mat4 FirstPersonCamera::getMatrix() const
{
	glm::mat4 ret(1.0f);
	ret = glm::rotate(ret, rotation_.x, glm::vec3(1, 0, 0));
	ret = glm::rotate(ret, rotation_.y, glm::vec3(0, 1, 0));
	ret = glm::translate(ret, position_);
	return ret;
}

glm::vec3 FirstPersonCamera::getPosition() const
{
	return {position_.x * -1, position_.y, position_.z * -1};
}

glm::vec2 FirstPersonCamera::getRotation() const
{
	return rotation_;
}

void FirstPersonCamera::move(const float angle, const float fac)
{
	position_.x += cos(rotation_.y + glm::radians(angle)) * fac;
	position_.z += sin(rotation_.y + glm::radians(angle)) * fac;
}
