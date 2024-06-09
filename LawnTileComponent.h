#pragma once
#include <vector>

#include "DrawComponent.h"
#include "tigl.h"

class Texture;
enum TileAction;

class LawnTileComponent : public DrawComponent
{
	std::vector<tigl::Vertex> unmowedVerts_, mowedVerts_;
	std::shared_ptr<Texture> texture_;
	float greenMult_;
public:
	bool selected = false;
	bool mowed = false;

	LawnTileComponent(const glm::vec3& size, const std::shared_ptr<Texture>& texture, float greenMult);

	void draw() override;
	void onClick(TileAction action);
};

