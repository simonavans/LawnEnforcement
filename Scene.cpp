#include "Scene.h"

#include <iostream>

#include "CubeComponent.h"
#include "FirstPersonCamera.h"
#include "Game.h"
#include "GameObject.h"
#include "LawnTileComponent.h"
#include "ModelComponent.h"
#include "MyCppFrustrations.h"
#include "TileType.h"

Scene::Scene(Game* game, std::vector<std::shared_ptr<GameObject>>& tools, const Settings settings)
	: game_(game), settings_(settings)
{
	// Add tools to objects to draw
	objects.insert(objects.end(), tools.begin(), tools.end());

	// Load in all textures (order matters)
	digitTextures_.push_back(std::make_shared<Texture>("assets/textures/grass.jpg"));
	for (int i = 1; i < 9; i++)
	{
		digitTextures_.push_back(
			std::make_shared<Texture>("assets/textures/digit_" + std::to_string(i) + ".png")
		);
	}
	digitTextures_.push_back(std::make_shared<Texture>("assets/textures/flag.png"));
	digitTextures_.push_back(std::make_shared<Texture>("assets/textures/bomb.png"));

	// Create ground plane
	const auto groundPlane = std::make_shared<GameObject>(game);
	groundPlane->position = glm::vec3(4.5f, -1.1f, 4.5f);
	groundPlane->addComponent(std::make_shared<CubeComponent>(
		glm::vec3(5, 0.1f, 5),
		glm::vec4(0.3f, 0.4f, 0.2f, 1)));
	objects.push_back(groundPlane);

	generateLawn();
}

void Scene::update(const float deltaTime) const
{
	for (const auto& object : objects)
		object->update(deltaTime);
}

void Scene::draw() const
{
	tigl::shader->enableAlphaTest(true);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	tigl::shader->enableLighting(true);
	tigl::shader->setLightCount(1);
	tigl::shader->setLightDirectional(0, false);
	tigl::shader->setLightPosition(0, glm::vec3(5, 30, 5));
	tigl::shader->setLightAmbient(0, glm::vec3(0.6f, 0.6f, 0.55f));
	tigl::shader->setLightDiffuse(0, glm::vec3(0.2f, 0.4f, 0.4f));

	for (const auto& object : objects)
	{
		if (object->getComponent<ModelComponent>() && object != game_->equippedTool)
			continue;
		object->draw();
	}
}

void Scene::generateLawn()
{
	// Note: in this context, the y-axis means up/down. So the x-axis and z-axis are used.

	constexpr int lawnTileHeight = -1;

	// Create tiles
	for (int z = 0; z < settings_.mapSize; z++)
	{
		std::vector<std::shared_ptr<LawnTileComponent>> lawnTileRow;
		for (int x = 0; x < settings_.mapSize; x++)
		{
			auto lawnTile = std::make_shared<GameObject>(game_);
			lawnTile->position = glm::vec3(x, lawnTileHeight, z);

			// Random number (0.5 <= n < 0.8), to color grass slightly differently
			float grassColorMult = static_cast<float>(rand() % 3 + 5) / 10.0f;
			lawnTile->addComponent(std::make_shared<LawnTileComponent>(
				glm::vec3(0.49f, 0.1f, 0.49f),
				std::make_shared<std::vector<std::shared_ptr<Texture>>>(digitTextures_),
				grassColorMult));

			lawnTileRow.push_back(lawnTile->getComponent<LawnTileComponent>());
			objects.push_back(lawnTile);
		}
		lawnTileMap.push_back(lawnTileRow);
	}

	// Place mines
	int minesPlaced = 0;
	while (minesPlaced < settings_.mines)
	{
		// Place mines regardless of edge cases
		while (minesPlaced < settings_.mines)
		{
			const int randX = rand() % settings_.mapSize;
			const int randZ = rand() % settings_.mapSize;

			// Make tile a mine tile if it was a none tile
			if (lawnTileMap[randZ][randX]->tileType == TILE_TYPE_NONE)
			{
				lawnTileMap[randZ][randX]->tileType = TILE_TYPE_MINE;
				minesPlaced++;
			}
		}

		// Reserved tiles start at (3, 3) and end at (7, 7)
		constexpr int reservedXYStart = 3;
		constexpr int reservedXYEnd = 7;

		// Reserve a couple of tiles so the player can start with unmowed tiles
		for (int reservedY = reservedXYStart; reservedY <= reservedXYEnd; reservedY++)
			for (int reservedX = reservedXYStart; reservedX <= reservedXYEnd; reservedX++)
			{
				if ((reservedY == reservedXYStart && reservedX == reservedXYStart) ||
					(reservedY == reservedXYStart && reservedX == reservedXYEnd) ||
					(reservedY == reservedXYEnd && reservedX == reservedXYStart) ||
					(reservedY == reservedXYEnd && reservedX == reservedXYEnd))
					continue;

				const std::shared_ptr<LawnTileComponent> tile = lawnTileMap[reservedY][reservedX];
				if (tile->tileType == TILE_TYPE_MINE)
					minesPlaced--;
				tile->tileType = TILE_TYPE_NONE;
				tile->mowed = true;
			}
	}

	// Calculate mine neighbors for each none-tile
	for (int z = 0; z < settings_.mapSize; z++)
		for (int x = 0; x < settings_.mapSize; x++)
		{
			const std::shared_ptr<LawnTileComponent> tile = lawnTileMap[z][x];
			int mineNeighbors = 0;

			if (tile->tileType == TILE_TYPE_MINE)
				continue;

			// Loop through all neighbor positions relative to the tile in question
			for (int neighborZ = -1; neighborZ <= 1; neighborZ++)
				for (int neighborX = -1; neighborX <= 1; neighborX++)
				{
					try
					{
						// Check if there is a mine neighbor, but continue if the location was invalid
						if (lawnTileMap.at(z + neighborZ).at(x + neighborX)->tileType == TILE_TYPE_MINE)
							mineNeighbors++;
					}
					catch (const std::out_of_range&) {}
				}

			tile->tileType = static_cast<TileType>(mineNeighbors);
		}
}
