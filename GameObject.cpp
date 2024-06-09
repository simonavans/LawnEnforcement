#include "GameObject.h"

#include <glm/ext/matrix_transform.hpp>

#include "Component.h"
#include "DrawComponent.h"
#include "tigl.h"

GameObject::GameObject(Game* game)
{
	this->game = game;
}

void GameObject::update(const float deltaTime) const
{
	for (const auto& component : components_)
		component->update(deltaTime);
}

void GameObject::draw(const glm::mat4& parentMatrix) const
{
	if (!drawComponent_) return;

	glm::mat4 modelMatrix = parentMatrix;
	modelMatrix = glm::translate(modelMatrix, position);
	if (rotation.x != 0) modelMatrix = glm::rotate(modelMatrix, (float)glm::radians(rotation.x), glm::vec3(1, 0, 0));
	if (rotation.y != 0) modelMatrix = glm::rotate(modelMatrix, (float)glm::radians(rotation.y), glm::vec3(0, 1, 0));
	if (rotation.z != 0) modelMatrix = glm::rotate(modelMatrix, (float)glm::radians(rotation.z), glm::vec3(0, 0, 1));
	modelMatrix = glm::scale(modelMatrix, scale);

	tigl::shader->setModelMatrix(modelMatrix);
	drawComponent_->draw();
}

void GameObject::addComponent(const std::shared_ptr<Component>& component)
{
	component->setGameObject(this);
	components_.push_back(component);

	if (drawComponent_ == nullptr)
		drawComponent_ = std::dynamic_pointer_cast<DrawComponent>(component);
}

std::list<std::shared_ptr<Component>> GameObject::getComponents()
{
	return components_;
}

template <class T>
std::shared_ptr<T> GameObject::getComponent()
{
	for (auto component : components_)
	{
		std::shared_ptr<T> cast = std::dynamic_pointer_cast<T>(component);
		if (cast) return cast;
	}
	return nullptr;
}

template <class T>
void GameObject::removeComponent()
{
	components_.remove_if([](const std::shared_ptr<Component>& component)
		{
			std::shared_ptr<T> cast = std::dynamic_pointer_cast<T>(component);
			return cast != nullptr;
		});
}
