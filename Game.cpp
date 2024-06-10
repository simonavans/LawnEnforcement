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
#include "MyCppFrustrations.h"
#include "TileAction.h"

Game::Game(GLFWwindow* window, Settings settings) : window_(window), settings_(settings)
{
	camera_ = std::make_shared<FirstPersonCamera>(window);

	std::vector<std::shared_ptr<GameObject>> extraObjects;
	wieldingCube1_ = std::make_shared<GameObject>(this);
	wieldingCube1_->addComponent(std::make_shared<ModelComponent>(
		"assets/LawnMower/source/LawnMower/LawnMower.obj"));
	extraObjects.push_back(wieldingCube1_);

	wieldingCube2_ = std::make_shared<GameObject>(this);
	wieldingCube2_->addComponent(std::make_shared<ModelComponent>(
		"assets/SmallerFlag/source/SmallerFlag/SmallerFlag.obj"));
	extraObjects.push_back(wieldingCube2_);

	equippedCube = wieldingCube1_;

	scene = std::make_shared<Scene>(this, extraObjects, settings);
}

void Game::update(const float deltaTime) const
{
	camera_->update(window_, deltaTime);

	glm::vec3 cameraPosition = camera_->getPosition();
	const glm::vec2 cameraRotation = camera_->getRotation(); 
	glm::vec3 forwardVec = {
		sin(cameraRotation.y),
		0,
		-(cos(cameraRotation.y) * cos(cameraRotation.x)),
	};
	forwardVec = glm::normalize(forwardVec);
	cameraPosition.y -= 0.7f;
	const glm::vec3 forwardPos = cameraPosition + forwardVec;

	equippedCube->position = forwardPos;
	equippedCube->rotation = { 0, -glm::degrees(cameraRotation.y) + 180, 0 };

	static int clickCode;

	int correctFlagsPlaced = 0;
	for (const auto& object : scene->objects)
	{
		const auto lawnTile = object->getComponent<LawnTileComponent>();
		if (!lawnTile)
			continue;

		if (lawnTile->tileType == TILE_TYPE_MINE && lawnTile->flagged)
			correctFlagsPlaced++;

		if (abs(object->position.x - forwardPos.x) < 0.5f && abs(object->position.z - forwardPos.z) < 0.5f)
		{
			const int keyEvent = glfwGetMouseButton(window_, GLFW_MOUSE_BUTTON_1);
			if (keyEvent == GLFW_PRESS && clickCode != GLFW_RELEASE)
			{
				clickCode = GLFW_RELEASE;
				if (equippedCube == wieldingCube1_)
					lawnTile->onClick(TILE_ACTION_MOW);
				else if (equippedCube == wieldingCube2_ && !lawnTile->mowed && !lawnTile->reserved)
					lawnTile->onClick(TILE_ACTION_FLAG);
			}
			else if (keyEvent == GLFW_RELEASE)
				clickCode = -1;
			lawnTile->selected = true;
		}
		else if (lawnTile->selected == true)
			lawnTile->selected = false;
	}
	
	if (correctFlagsPlaced == settings_.mines)
	{
		bool gameWon = true;
		for (const auto& row : scene->lawnTiles2D)
			for (const auto& tile : row)
				if (tile->tileType != TILE_TYPE_NONE && tile->tileType != TILE_TYPE_MINE && !tile->mowed && !tile->reserved)
					gameWon = false;

		if (gameWon)
			for (const auto& row : scene->lawnTiles2D)
				for (const auto& tile : row)
					tile->mowed = true;
	}

	scene->update(deltaTime);
}

void Game::draw() const
{
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
	if (equippedCube == wieldingCube1_)
		equippedCube = wieldingCube2_;
	else
		equippedCube = wieldingCube1_;
}

std::shared_ptr<FirstPersonCamera> Game::getCamera() const
{
	return camera_;
}
