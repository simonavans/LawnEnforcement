#pragma once
#include <memory>

#include "GameObject.h"

class Scene;
struct GLFWwindow;
class FirstPersonCamera;

class Game
{
	GLFWwindow* window_;
	std::shared_ptr<GameObject> wieldingCube1_, wieldingCube2_;
	std::shared_ptr<FirstPersonCamera> camera_;
public:
	std::shared_ptr<GameObject> equippedCube;
	std::shared_ptr<Scene> scene;

	Game(GLFWwindow* window);
	void update(float deltaTime);
	void draw();
	void swapTools();

	std::shared_ptr<FirstPersonCamera> getCamera() const;
};
