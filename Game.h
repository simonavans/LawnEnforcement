#pragma once
#include <memory>

#include "GameObject.h"
#include "SettingsLoader.h"

class Scene;
struct GLFWwindow;
class FirstPersonCamera;

class Game
{
	GLFWwindow* window_;
	std::shared_ptr<GameObject> wieldingCube1_, wieldingCube2_;
	std::shared_ptr<FirstPersonCamera> camera_;
	Settings settings_;
public:
	std::shared_ptr<GameObject> equippedCube;
	std::shared_ptr<Scene> scene;

	Game(GLFWwindow* window, Settings settings);
	void update(float deltaTime) const;
	void draw() const;
	void swapTools();

	std::shared_ptr<FirstPersonCamera> getCamera() const;
};
