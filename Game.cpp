#include "Game.h"

#include <iostream>
#include <GL/glew.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "FirstPersonCamera.h"
#include "GameObject.h"
#include "LawnTileComponent.h"
#include "ModelComponent.h"
#include "Scene.h"
#include "tigl.h"
#include "GLFW/glfw3.h"
#include "TileAction.h"

Game::Game(GLFWwindow* window, Settings settings) : window_(window), settings_(settings)
{
	camera_ = std::make_shared<FirstPersonCamera>(window);

	// Instantiate tools
	std::vector<std::shared_ptr<GameObject>> tools;
	lawnMowerTool_ = std::make_shared<GameObject>(this);
	lawnMowerTool_->addComponent(std::make_shared<ModelComponent>(
		"assets/LawnMower/source/LawnMower/LawnMower.obj"));
	tools.push_back(lawnMowerTool_);

	flagTool_ = std::make_shared<GameObject>(this);
	flagTool_->addComponent(std::make_shared<ModelComponent>(
		"assets/SmallerFlag/source/SmallerFlag/SmallerFlag.obj"));
	tools.push_back(flagTool_);

	equippedTool = lawnMowerTool_;

	scene = std::make_shared<Scene>(this, tools, settings);
}

void Game::update(const float deltaTime)
{
	camera_->update(window_, deltaTime);

	// Set tool pos and rot to be in front of camera
	const glm::vec3 cameraPos = camera_->getPosition();
	const glm::vec2 cameraRot = camera_->getRotation(); 
	const glm::vec3 forwardPos = getCameraForwardPos(cameraPos, cameraRot);

	equippedTool->position = forwardPos;
	equippedTool->rotation = { 0, -glm::degrees(cameraRot.y) + 180, 0 };

	int correctFlagsPlaced = 0;
	bool allSafeTilesMowed = true;
	for (const auto& object : scene->objects)
	{
		const auto lawnTile = object->getComponent<LawnTileComponent>();
		if (!lawnTile)
			continue;

		if ((gameOver_ || gameWon_) && !lawnTile->mowed)
			lawnTile->mowed = true;

		if (lawnTile->tileType == TILE_TYPE_MINE && lawnTile->flagged)
			correctFlagsPlaced++;

		// Check if this tile is mowed for game win condition
		if (lawnTile->tileType != TILE_TYPE_NONE &&
			lawnTile->tileType != TILE_TYPE_MINE &&
			!lawnTile->mowed)
		{
			allSafeTilesMowed = false;
		}

		constexpr float maxDistanceToSelect = 0.5f;

		// Handle tile selection and clicking
		// Check if the tile is close enough to the tool
		if (abs(object->position.x - forwardPos.x) < maxDistanceToSelect &&
			abs(object->position.z - forwardPos.z) < maxDistanceToSelect &&
			!lawnTile->mowed)
		{
			lawnTile->selected = true;
			handleClick(lawnTile);
		}
		else if (lawnTile->selected)
			lawnTile->selected = false;
	}

	// Game is won if all flags were placed correctly and all safe tiles were mowed
	gameWon_ = correctFlagsPlaced == settings_.mines && allSafeTilesMowed;

	scene->update(deltaTime);
}

void Game::draw() const
{
	constexpr glm::vec4 winColor(0.3f, 0.9f, 0.4f, 1.0f);
	constexpr glm::vec4 loseColor(0.9f, 0.3f, 0.2f, 1.0f);
	constexpr glm::vec4 skyColor(0.3f, 0.4f, 0.6f, 1.0f);

	if (gameWon_)
		glClearColor(winColor.x, winColor.y, winColor.z, winColor.w);
	else if (gameOver_)
		glClearColor(loseColor.x, loseColor.y, loseColor.z, loseColor.w);
	else
		glClearColor(skyColor.x, skyColor.y, skyColor.z, skyColor.w);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	const glm::mat4 projectionMatrix = glm::perspective(
		glm::radians(75.0f),
		static_cast<float>(viewport[2]) / static_cast<float>(viewport[3]),
		0.01f,
		20.0f
	);

	tigl::shader->setProjectionMatrix(projectionMatrix);
	tigl::shader->setViewMatrix(camera_->getMatrix());
	tigl::shader->setModelMatrix(glm::mat4(1.0f));

	scene->draw();
}

void Game::swapTools()
{
	if (equippedTool == lawnMowerTool_)
		equippedTool = flagTool_;
	else
		equippedTool = lawnMowerTool_;
}

glm::vec3 Game::getCameraForwardPos(const glm::vec3 cameraPos, const glm::vec2 cameraRot)
{
	glm::vec3 pos = cameraPos;

	// Calculate position forward of the camera
	glm::vec3 forwardVec = {
		sin(cameraRot.y),
		0,
		-(cos(cameraRot.y) * cos(cameraRot.x)),
	};
	forwardVec = glm::normalize(forwardVec);

	// Lower position to make tools touch the ground
	pos.y -= 0.7f;

	return pos + forwardVec;
}

void Game::handleClick(const std::shared_ptr<LawnTileComponent>& lawnTile)
{
	static int clickCode;
	const int mouseBtnEvent = glfwGetMouseButton(window_, GLFW_MOUSE_BUTTON_1);

	// If button was pressed but not already pressed before
	if (mouseBtnEvent == GLFW_PRESS && clickCode != GLFW_RELEASE)
	{
		// Set so the button is already pressed
		clickCode = GLFW_RELEASE;

		if (equippedTool == lawnMowerTool_)
		{
			lawnTile->onClick(TILE_ACTION_MOW);
			if (lawnTile->tileType == TILE_TYPE_MINE)
				gameOver_ = true;
		}
		else if (equippedTool == flagTool_)
			lawnTile->onClick(TILE_ACTION_FLAG);
	}
	// If button was released, set click code to not be already pressed
	else if (mouseBtnEvent == GLFW_RELEASE)
		clickCode = -1;
}
