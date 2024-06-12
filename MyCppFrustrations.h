#pragma once
#include <memory>

#include "GameObject.h"

// C++ linker is a little silly because it complains when
// this method is already defined in another translation
// unit. So I have to do it the ugly way...
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
