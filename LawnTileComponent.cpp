#include "LawnTileComponent.h"

#include <iostream>
#include <stdexcept>

#include "Texture.h"
#include "TileAction.h"

LawnTileComponent::LawnTileComponent(
		const glm::vec3& size,
		const std::shared_ptr<std::vector<std::shared_ptr<Texture>>>& digitTextures,
		const float greenMult
	)	: greenMult_(greenMult), digitTextures_(digitTextures)
{
#pragma region mowedVerts_
	//bottom
	unmowedVerts_.push_back(tigl::Vertex::PTN(glm::vec3(-size.x, -size.y, -size.z), glm::vec2(0, 0), glm::vec3(0, -1, 0)));
	unmowedVerts_.push_back(tigl::Vertex::PTN(glm::vec3(size.x, -size.y, -size.z), glm::vec2(1, 0), glm::vec3(0, -1, 0)));
	unmowedVerts_.push_back(tigl::Vertex::PTN(glm::vec3(size.x, -size.y, size.z), glm::vec2(1, 1), glm::vec3(0, -1, 0)));
	unmowedVerts_.push_back(tigl::Vertex::PTN(glm::vec3(-size.x, -size.y, size.z), glm::vec2(0, 1), glm::vec3(0, -1, 0)));

	//top
	unmowedVerts_.push_back(tigl::Vertex::PTN(glm::vec3(-size.x, size.y, -size.z), glm::vec2(1, 1), glm::vec3(0, 1, 0)));
	unmowedVerts_.push_back(tigl::Vertex::PTN(glm::vec3(size.x, size.y, -size.z), glm::vec2(1, 0), glm::vec3(0, 1, 0)));
	unmowedVerts_.push_back(tigl::Vertex::PTN(glm::vec3(size.x, size.y, size.z), glm::vec2(0, 0), glm::vec3(0, 1, 0)));
	unmowedVerts_.push_back(tigl::Vertex::PTN(glm::vec3(-size.x, size.y, size.z), glm::vec2(0, 1), glm::vec3(0, 1, 0)));

	//left
	unmowedVerts_.push_back(tigl::Vertex::PTN(glm::vec3(size.x, -size.y, -size.z), glm::vec2(1, 0), glm::vec3(1, 0, 0)));
	unmowedVerts_.push_back(tigl::Vertex::PTN(glm::vec3(size.x, size.y, -size.z), glm::vec2(1, 1), glm::vec3(1, 0, 0)));
	unmowedVerts_.push_back(tigl::Vertex::PTN(glm::vec3(size.x, size.y, size.z), glm::vec2(0, 1), glm::vec3(1, 0, 0)));
	unmowedVerts_.push_back(tigl::Vertex::PTN(glm::vec3(size.x, -size.y, size.z), glm::vec2(0, 0), glm::vec3(1, 0, 0)));

	//right
	unmowedVerts_.push_back(tigl::Vertex::PTN(glm::vec3(-size.x, -size.y, -size.z), glm::vec2(0, 0), glm::vec3(-1, 0, 0)));
	unmowedVerts_.push_back(tigl::Vertex::PTN(glm::vec3(-size.x, size.y, -size.z), glm::vec2(0, 1), glm::vec3(-1, 0, 0)));
	unmowedVerts_.push_back(tigl::Vertex::PTN(glm::vec3(-size.x, size.y, size.z), glm::vec2(1, 1), glm::vec3(-1, 0, 0)));
	unmowedVerts_.push_back(tigl::Vertex::PTN(glm::vec3(-size.x, -size.y, size.z), glm::vec2(1, 0), glm::vec3(-1, 0, 0)));

	//back
	unmowedVerts_.push_back(tigl::Vertex::PTN(glm::vec3(-size.x, -size.y, -size.z), glm::vec2(0, 0), glm::vec3(0, 0, -1)));
	unmowedVerts_.push_back(tigl::Vertex::PTN(glm::vec3(-size.x, size.y, -size.z), glm::vec2(0, 1), glm::vec3(0, 0, -1)));
	unmowedVerts_.push_back(tigl::Vertex::PTN(glm::vec3(size.x, size.y, -size.z), glm::vec2(1, 1), glm::vec3(0, 0, -1)));
	unmowedVerts_.push_back(tigl::Vertex::PTN(glm::vec3(size.x, -size.y, -size.z), glm::vec2(1, 0), glm::vec3(0, 0, -1)));

	//front
	unmowedVerts_.push_back(tigl::Vertex::PTN(glm::vec3(-size.x, -size.y, size.z), glm::vec2(0, 0), glm::vec3(0, 0, 1)));
	unmowedVerts_.push_back(tigl::Vertex::PTN(glm::vec3(-size.x, size.y, size.z), glm::vec2(0, 1), glm::vec3(0, 0, 1)));
	unmowedVerts_.push_back(tigl::Vertex::PTN(glm::vec3(size.x, size.y, size.z), glm::vec2(1, 1), glm::vec3(0, 0, 1)));
	unmowedVerts_.push_back(tigl::Vertex::PTN(glm::vec3(size.x, -size.y, size.z), glm::vec2(1, 0), glm::vec3(0, 0, 1)));
#pragma endregion

#pragma region unmowedVerts_
	//bottom
	mowedVerts_.push_back(tigl::Vertex::PTN(glm::vec3(-size.x, -size.y, -size.z), glm::vec2(0, 0), glm::vec3(0, -1, 0)));
	mowedVerts_.push_back(tigl::Vertex::PTN(glm::vec3(size.x, -size.y, -size.z), glm::vec2(1, 0), glm::vec3(0, -1, 0)));
	mowedVerts_.push_back(tigl::Vertex::PTN(glm::vec3(size.x, -size.y, size.z), glm::vec2(1, 1), glm::vec3(0, -1, 0)));
	mowedVerts_.push_back(tigl::Vertex::PTN(glm::vec3(-size.x, -size.y, size.z), glm::vec2(0, 1), glm::vec3(0, -1, 0)));

	//top
	mowedVerts_.push_back(tigl::Vertex::PTN(glm::vec3(-size.x, size.y * 2, -size.z), glm::vec2(1, 1), glm::vec3(0, 1, 0)));
	mowedVerts_.push_back(tigl::Vertex::PTN(glm::vec3(size.x, size.y * 2, -size.z), glm::vec2(1, 0), glm::vec3(0, 1, 0)));
	mowedVerts_.push_back(tigl::Vertex::PTN(glm::vec3(size.x, size.y * 2, size.z), glm::vec2(0, 0), glm::vec3(0, 1, 0)));
	mowedVerts_.push_back(tigl::Vertex::PTN(glm::vec3(-size.x, size.y * 2, size.z), glm::vec2(0, 1), glm::vec3(0, 1, 0)));

	//left
	mowedVerts_.push_back(tigl::Vertex::PTN(glm::vec3(size.x, -size.y, -size.z), glm::vec2(1, 0), glm::vec3(1, 0, 0)));
	mowedVerts_.push_back(tigl::Vertex::PTN(glm::vec3(size.x, size.y * 2, -size.z), glm::vec2(1, 1), glm::vec3(1, 0, 0)));
	mowedVerts_.push_back(tigl::Vertex::PTN(glm::vec3(size.x, size.y * 2, size.z), glm::vec2(0, 1), glm::vec3(1, 0, 0)));
	mowedVerts_.push_back(tigl::Vertex::PTN(glm::vec3(size.x, -size.y, size.z), glm::vec2(0, 0), glm::vec3(1, 0, 0)));

	//right
	mowedVerts_.push_back(tigl::Vertex::PTN(glm::vec3(-size.x, -size.y, -size.z), glm::vec2(0, 0), glm::vec3(-1, 0, 0)));
	mowedVerts_.push_back(tigl::Vertex::PTN(glm::vec3(-size.x, size.y * 2, -size.z), glm::vec2(0, 1), glm::vec3(-1, 0, 0)));
	mowedVerts_.push_back(tigl::Vertex::PTN(glm::vec3(-size.x, size.y * 2, size.z), glm::vec2(1, 1), glm::vec3(-1, 0, 0)));
	mowedVerts_.push_back(tigl::Vertex::PTN(glm::vec3(-size.x, -size.y, size.z), glm::vec2(1, 0), glm::vec3(-1, 0, 0)));

	//back
	mowedVerts_.push_back(tigl::Vertex::PTN(glm::vec3(-size.x, -size.y, -size.z), glm::vec2(0, 0), glm::vec3(0, 0, -1)));
	mowedVerts_.push_back(tigl::Vertex::PTN(glm::vec3(-size.x, size.y * 2, -size.z), glm::vec2(0, 1), glm::vec3(0, 0, -1)));
	mowedVerts_.push_back(tigl::Vertex::PTN(glm::vec3(size.x, size.y * 2, -size.z), glm::vec2(1, 1), glm::vec3(0, 0, -1)));
	mowedVerts_.push_back(tigl::Vertex::PTN(glm::vec3(size.x, -size.y, -size.z), glm::vec2(1, 0), glm::vec3(0, 0, -1)));

	//front
	mowedVerts_.push_back(tigl::Vertex::PTN(glm::vec3(-size.x, -size.y, size.z), glm::vec2(0, 0), glm::vec3(0, 0, 1)));
	mowedVerts_.push_back(tigl::Vertex::PTN(glm::vec3(-size.x, size.y * 2, size.z), glm::vec2(0, 1), glm::vec3(0, 0, 1)));
	mowedVerts_.push_back(tigl::Vertex::PTN(glm::vec3(size.x, size.y * 2, size.z), glm::vec2(1, 1), glm::vec3(0, 0, 1)));
	mowedVerts_.push_back(tigl::Vertex::PTN(glm::vec3(size.x, -size.y, size.z), glm::vec2(1, 0), glm::vec3(0, 0, 1)));
#pragma endregion
}

void LawnTileComponent::draw()
{
	tigl::shader->enableColorMult(true);
	if (mowed || reserved)
		tigl::shader->setColorMult(glm::vec4(0.4f, 0.6f, 0.4f, 1));
	else if (selected && !mowed && !reserved)
		tigl::shader->setColorMult(glm::vec4(0.4f, 0.3f, 0.4f, 1));
	else
		tigl::shader->setColorMult(glm::vec4(0.5f, greenMult_, 0.5f, 1));

	if (mowed && tileType == TILE_TYPE_MINE)
		digitTextures_->at(10)->bind();
	else if (flagged)
		digitTextures_->at(9)->bind();
	else if ((mowed || reserved) && tileType != TILE_TYPE_MINE)
		digitTextures_->at(tileType)->bind();
	else
		digitTextures_->at(0)->bind();

	if (mowed || reserved)
		tigl::drawVertices(GL_QUADS, unmowedVerts_);
	else
		tigl::drawVertices(GL_QUADS, mowedVerts_);

	if (flagged)
		digitTextures_->at(9)->unbind();
	else if ((mowed || reserved) && tileType != TILE_TYPE_MINE)
		digitTextures_->at(tileType)->unbind();
	else
		digitTextures_->at(0)->unbind();

	tigl::shader->enableColorMult(false);
}

bool LawnTileComponent::onClick(const TileAction action)
{
	bool bombExploded = false;
	switch (action)
	{
	case TILE_ACTION_MOW:
		if (tileType == TILE_TYPE_MINE && !mowed)
			bombExploded = true;
		mowed = true;
		return bombExploded;
	case TILE_ACTION_FLAG:
		flagged = !flagged;
		return false;
	}
	return false;
}
