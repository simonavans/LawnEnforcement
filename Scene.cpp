#include "Scene.h"

#include <algorithm>
#include <iostream>

#include "CubeComponent.h"
#include "FirstPersonCamera.h"
#include "Game.h"
#include "GameObject.h"
#include "LawnTileComponent.h"
#include "ModelComponent.h"
#include "MyCppFrustrations.h"
#include "TileType.h"

Scene::Scene(Game* game, std::vector<std::shared_ptr<GameObject>>& extraObjects)
{
	this->game_ = game;
	objects.insert(objects.end(), extraObjects.begin(), extraObjects.end());

	std::vector<std::shared_ptr<Texture>> digitTextures;
	digitTextures.push_back(std::make_shared<Texture>("assets/textures/grass.jpg"));
	for (int i = 1; i < 9; i++)
	{
		digitTextures.push_back(
			std::make_shared<Texture>("assets/textures/digit_" + std::to_string(i) + ".png")
		);
	}
	digitTextures.push_back(std::make_shared<Texture>("assets/textures/flag.png"));

	std::shared_ptr<GameObject> groundPlane = std::make_shared<GameObject>(game);
	groundPlane->position = glm::vec3(4.5f, -1.1f, 4.5f);
	groundPlane->addComponent(std::make_shared<CubeComponent>(
		glm::vec3(5, 0.1f, 5),
		glm::vec4(0.3f, 0.4f, 0.2f, 0)));
	objects.push_back(groundPlane);

	for (int z = 0; z < 10; z++)
	{
		std::vector<std::shared_ptr<LawnTileComponent>> lawnTiles1D;
		for (int x = 0; x < 10; x++)
		{
			std::shared_ptr<GameObject> lawnTile = std::make_shared<GameObject>(game);
			lawnTile->position = glm::vec3(x, -1, z);

			float randNum = static_cast<float>(rand() % 3 + 5) / 10.0f;
			lawnTile->addComponent(std::make_shared<LawnTileComponent>(
				glm::vec3(0.49f, 0.1f, 0.49f),
				std::make_shared<std::vector<std::shared_ptr<Texture>>>(digitTextures),
				randNum));

			lawnTiles1D.push_back(lawnTile->getComponent<LawnTileComponent>());
			objects.push_back(lawnTile);
		}
		lawnTiles2D.push_back(lawnTiles1D);
	}

	int bombsPlaced = 0;
	while (bombsPlaced < 15)
	{
		while (bombsPlaced < 15)
		{
			const int randX = rand() % 10;
			const int randZ = rand() % 10;

			if (lawnTiles2D[randZ][randX]->tileType == TILE_TYPE_NONE)
			{
				lawnTiles2D[randZ][randX]->tileType = TILE_TYPE_BOMB;
				bombsPlaced++;
			}

		}

		for (int reservedY = 3; reservedY < 8; reservedY++)
			for (int reservedX = 3; reservedX < 8; reservedX++)
			{
				if ((reservedY == 3 && reservedX == 3) ||
					(reservedY == 3 && reservedX == 7) ||
					(reservedY == 7 && reservedX == 3) ||
					(reservedY == 7 && reservedX == 7))
					continue;

				const std::shared_ptr<LawnTileComponent> tile = lawnTiles2D[reservedY][reservedX];
				if (tile->tileType == TILE_TYPE_BOMB)
					bombsPlaced--;
				tile->tileType = TILE_TYPE_NONE;
				tile->reserved = true;
			}
	}

	for (int y = 0; y < 10; y++)
		for (int x = 0; x < 10; x++)
		{
			const std::shared_ptr<LawnTileComponent> tile = lawnTiles2D[y][x];
			int bombNeighbors = 0;

			if (tile->tileType == TILE_TYPE_BOMB)
				continue;

			for (int neighborY = -1; neighborY <= 1; neighborY++)
				for (int neighborX = -1; neighborX <= 1; neighborX++)
				{
					try
					{
						if (lawnTiles2D.at(y + neighborY).at(x + neighborX)->tileType == TILE_TYPE_BOMB)
							bombNeighbors++;
					}
					catch (const std::out_of_range&) {}
				}
			tile->tileType = static_cast<TileType>(bombNeighbors);
		}
}

void Scene::update(const float deltaTime)
{
	for (const auto& object : objects)
		object->update(deltaTime);
}


void Scene::draw()
{
	tigl::shader->enableAlphaTest(true);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	tigl::shader->enableLighting(true);
	tigl::shader->setLightCount(1);
	tigl::shader->setLightDirectional(0, false);
	tigl::shader->setLightPosition(0, glm::vec3(5, 5, 5));
	tigl::shader->setLightAmbient(0, glm::vec3(0.1f, 0.1f, 0.15f));
	tigl::shader->setLightDiffuse(0, glm::vec3(0.8f, 0.8f, 0.8f));

	for (const auto& object : objects)
	{
		if (object->getComponent<ModelComponent>() && object != game_->equippedCube)
			continue;
		object->draw();
	}
}
