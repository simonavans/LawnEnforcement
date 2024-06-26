#pragma once
#include <glm/glm.hpp>

#include "SettingsLoader.h"

struct GLFWwindow;

class FirstPersonCamera
{
	glm::vec3 position_ = glm::vec3(-5, 0, -5);
	glm::vec2 rotation_ = glm::vec2(0, 0);
	Settings settings_;
public:
	FirstPersonCamera(GLFWwindow* window, const Settings& settings);
	void update(GLFWwindow* window, float deltaTime);
	glm::mat4 getMatrix() const;
	glm::vec3 getPosition() const;
	glm::vec2 getRotation() const;
private:
	void move(float angle, float fac);
	bool isInBounds() const;
};

