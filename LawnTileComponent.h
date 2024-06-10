#pragma once
#include <vector>

#include "DrawComponent.h"
#include "tigl.h"
#include "TileType.h"

class Texture;
enum TileAction;

class LawnTileComponent : public DrawComponent
{
	std::vector<tigl::Vertex> unmowedVerts_, mowedVerts_;
	float greenMult_;
	std::shared_ptr<std::vector<std::shared_ptr<Texture>>> digitTextures_;
public:
	bool selected = false;
	bool mowed = false;
	bool reserved = false;
	bool flagged = false;
	TileType tileType = TILE_TYPE_NONE;

		LawnTileComponent(
		const glm::vec3& size,
		const std::shared_ptr<std::vector<std::shared_ptr<Texture>>>& digitTextures,
		float greenMult
	);

	void draw() override;
	void onClick(TileAction action);
};

