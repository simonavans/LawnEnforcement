#pragma once
#include <memory>

#include "GameObject.h"

// Don't mind this method declaration,
// apparently C++ LOVES to complain if I don't
// put this duplicate definition here ;)
template <class T>
std::shared_ptr<T> GameObject::getComponent()
{
	for (const auto& component : components_)
	{
		std::shared_ptr<T> cast = std::dynamic_pointer_cast<T>(component);
		if (cast) return cast;
	}
	return nullptr;
}
