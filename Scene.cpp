#include "Scene.h"

#include <iostream>

#include "CubeComponent.h"
#include "FirstPersonCamera.h"
#include "Game.h"
#include "GameObject.h"
#include "LawnTileComponent.h"
#include "ModelComponent.h"
#include "MyCppFrustrations.h"

Scene::Scene(Game* game, std::vector<std::shared_ptr<GameObject>>& extraObjects)
{
	this->game_ = game;
	objects.insert(objects.end(), extraObjects.begin(), extraObjects.end());

	std::shared_ptr<GameObject> groundPlane = std::make_shared<GameObject>(game);
	groundPlane->position = glm::vec3(4.5f, -1.1f, 4.5f);
	groundPlane->addComponent(std::make_shared<CubeComponent>(
		glm::vec3(5, 0.1f, 5),
		glm::vec4(0.3f, 0.4f, 0.2f, 0)));
	objects.push_back(groundPlane);

	for (int z = 0; z < 10; z++)
		for (int x = 0; x < 10; x++)
		{
			std::shared_ptr<GameObject> lawnTile = std::make_shared<GameObject>(game);
			lawnTile->position = glm::vec3(x, -1, z);

			float randNum = static_cast<float>(rand() % 3 + 5) / 10.0f;
			lawnTile->addComponent(std::make_shared<LawnTileComponent>(
				glm::vec3(0.49f, 0.1f, 0.49f),
				grassTexture_,
				randNum));
			objects.push_back(lawnTile);
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
