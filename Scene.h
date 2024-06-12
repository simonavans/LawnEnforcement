#pragma once
#include <list>
#include <memory>
#include <vector>

#include "SettingsLoader.h"
#include "Texture.h"

class Texture;
class Game;
class GameObject;
class LawnTileComponent;

class Scene
{
	std::vector<std::shared_ptr<Texture>> digitTextures_;
	Game* game_;
	Settings settings_;
public:
	std::shared_ptr<GameObject> playerObject;
	std::list<std::shared_ptr<GameObject>> objects;
	std::vector<std::vector<std::shared_ptr<LawnTileComponent>>> lawnTileMap;

	// Using raw pointers, because passing 'this' to a shared pointer
	// causes weird double-free issues (shared pointer may point to heap memory,
	// thus causing double-free? Anyways, it's an edge case not discussed in the
	// lessons, so I used the raw variant.
	Scene(Game* game, std::vector<std::shared_ptr<GameObject>>& tools, Settings settings);
	void update(float deltaTime) const;
	void draw() const;
private:
	void generateLawn();
};
