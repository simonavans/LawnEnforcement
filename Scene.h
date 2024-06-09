#pragma once
#include <list>
#include <memory>
#include <vector>

#include "Texture.h"

class Texture;
class Game;
class GameObject;

class Scene
{
	std::shared_ptr<Texture> grassTexture_ = std::make_shared<Texture>("assets/textures/grass.jpg");
	Game* game_;
public:
	std::shared_ptr<GameObject> playerObject;
	std::list<std::shared_ptr<GameObject>> objects;

	// Using raw pointers, because passing 'this' to a shared pointer
	// causes weird double-free issues (shared pointer may point to heap memory,
	// thus causing double-free? Anyways, it's an edge case not discussed in the
	// lessons, so I used the raw variant.
	Scene(Game* game, std::vector<std::shared_ptr<GameObject>>& extraObjects);
	void update(float deltaTime);
	void draw();
};
