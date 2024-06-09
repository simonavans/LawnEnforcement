#pragma once

#include "Component.h"

class DrawComponent : public Component
{
public:
	DrawComponent() = default;
	virtual void draw() = 0;
};
