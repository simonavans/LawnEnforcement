#pragma once
#include <vector>

#include "DrawComponent.h"

namespace tigl
{
	struct Vertex;
}

class FlagComponent : public DrawComponent
{
	std::vector<tigl::Vertex> verts_;
public:
	FlagComponent();

	void draw() override;
};

