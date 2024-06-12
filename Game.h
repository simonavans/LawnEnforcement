#pragma once
#include <memory>

#include "GameObject.h"
#include "SettingsLoader.h"

class Texture;
class Scene;
struct GLFWwindow;
class FirstPersonCamera;

class Game
{
	GLFWwindow* window_;
	std::shared_ptr<GameObject> wieldingCube1_, wieldingCube2_;
	std::shared_ptr<FirstPersonCamera> camera_;
	Settings settings_;
	bool gameOver_ = false;
	bool gameWon_ = false;
public:
	std::shared_ptr<GameObject> equippedCube;
	std::shared_ptr<Scene> scene;

	Game(GLFWwindow* window, Settings settings);
	void update(float deltaTime);
	void draw() const;
	void swapTools();

	std::shared_ptr<FirstPersonCamera> getCamera() const;
};
