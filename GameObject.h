#pragma once
#include <memory>
#include <list>
#include <glm/glm.hpp>
#include <glm/fwd.hpp>
#include <glm/vec3.hpp>

class Game;
class Component;
class DrawComponent;

class GameObject
{
public:
	glm::vec3 position = glm::vec3(0);
	glm::vec3 rotation = glm::vec3(0);
	glm::vec3 scale = glm::vec3(1);
private:
	std::shared_ptr<DrawComponent> drawComponent_;
	std::list<std::shared_ptr<Component>> components_;
public:
	Game* game;

	GameObject(Game* game);
	~GameObject() = default;

	void update(float deltaTime) const;
	void draw(const glm::mat4& parentMatrix = glm::mat4(1.0f)) const;

	void addComponent(const std::shared_ptr<Component>& component);
	std::list<std::shared_ptr<Component>> getComponents();

	template<class T>
	std::shared_ptr<T> getComponent();

	template<class T>
	void removeComponent();
};

