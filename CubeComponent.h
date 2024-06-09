#pragma once
#include <vector>

#include "DrawComponent.h"
#include "tigl.h"

class Texture;

class CubeComponent : public DrawComponent
{
	std::vector<tigl::Vertex> verts_;
	std::shared_ptr<Texture> texture_;
public:
	CubeComponent(const glm::vec3& size, const std::shared_ptr<Texture>& texture);
	CubeComponent(const glm::vec3& size, const glm::vec4& color);

	void draw() override;
};

