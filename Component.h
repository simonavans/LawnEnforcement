#pragma once

#include <memory>

class GameObject;

class Component
{
protected:
	GameObject* gameObject_;
public:
	Component() = default;
	virtual void update(float deltaTime) {}

	// Using raw pointers, because passing 'this' to a shared pointer
	// causes weird double-free issues (shared pointer may point to heap memory,
	// thus causing double-free? Anyways, it's an edge case not discussed in the
	// lessons, so I used the raw variant.
	void setGameObject(GameObject* gameObject) { this->gameObject_ = gameObject; }
};
