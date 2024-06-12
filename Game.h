#pragma once
#include <memory>

#include "GameObject.h"
#include "SettingsLoader.h"

class LawnTileComponent;
class Texture;
class Scene;
struct GLFWwindow;
class FirstPersonCamera;

class Game
{
	GLFWwindow* window_;
	std::shared_ptr<GameObject> lawnMowerTool_, flagTool_;
	std::shared_ptr<FirstPersonCamera> camera_;
	Settings settings_;
	bool gameOver_ = false;
	bool gameWon_ = false;
public:
	std::shared_ptr<GameObject> equippedTool;
	std::shared_ptr<Scene> scene;

	Game(GLFWwindow* window, Settings settings);
	void update(float deltaTime);
	void draw() const;
	void swapTools();

private:
	static glm::vec3 getCameraForwardPos(glm::vec3 cameraPos, glm::vec2 cameraRot);
	void handleClick(const std::shared_ptr<LawnTileComponent>& lawnTile);
};
