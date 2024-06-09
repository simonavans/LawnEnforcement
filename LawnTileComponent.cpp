#include "LawnTileComponent.h"

#include "Texture.h"
#include "TileAction.h"

LawnTileComponent::LawnTileComponent(const glm::vec3& size, const std::shared_ptr<Texture>& texture, const float greenMult)
	: texture_(texture), greenMult_(greenMult)
{
#pragma region mowedVerts_
	//bottom
	unmowedVerts_.push_back(tigl::Vertex::PTN(glm::vec3(-size.x, -size.y, -size.z), glm::vec2(0, 0), glm::vec3(0, -1, 0)));
	unmowedVerts_.push_back(tigl::Vertex::PTN(glm::vec3(size.x, -size.y, -size.z), glm::vec2(1, 0), glm::vec3(0, -1, 0)));
	unmowedVerts_.push_back(tigl::Vertex::PTN(glm::vec3(size.x, -size.y, size.z), glm::vec2(1, 1), glm::vec3(0, -1, 0)));
	unmowedVerts_.push_back(tigl::Vertex::PTN(glm::vec3(-size.x, -size.y, size.z), glm::vec2(0, 1), glm::vec3(0, -1, 0)));

	//top
	unmowedVerts_.push_back(tigl::Vertex::PTN(glm::vec3(-size.x, size.y, -size.z), glm::vec2(0, 0), glm::vec3(0, 1, 0)));
	unmowedVerts_.push_back(tigl::Vertex::PTN(glm::vec3(size.x, size.y, -size.z), glm::vec2(1, 0), glm::vec3(0, 1, 0)));
	unmowedVerts_.push_back(tigl::Vertex::PTN(glm::vec3(size.x, size.y, size.z), glm::vec2(1, 1), glm::vec3(0, 1, 0)));
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
	mowedVerts_.push_back(tigl::Vertex::PTN(glm::vec3(-size.x, size.y * 2, -size.z), glm::vec2(0, 0), glm::vec3(0, 1, 0)));
	mowedVerts_.push_back(tigl::Vertex::PTN(glm::vec3(size.x, size.y * 2, -size.z), glm::vec2(1, 0), glm::vec3(0, 1, 0)));
	mowedVerts_.push_back(tigl::Vertex::PTN(glm::vec3(size.x, size.y * 2, size.z), glm::vec2(1, 1), glm::vec3(0, 1, 0)));
	mowedVerts_.push_back(tigl::Vertex::PTN(glm::vec3(-size.x, size.y * 2, size.z), glm::vec2(0, 1), glm::vec3(0, 1, 0)));

	//left
	mowedVerts_.push_back(tigl::Vertex::PTN(glm::vec3(size.x, -size.y, -size.z), glm::vec2(1, 0), glm::vec3(1, 0, 0)));
	mowedVerts_.push_back(tigl::Vertex::PTN(glm::vec3(size.x, size.y, -size.z), glm::vec2(1, 1), glm::vec3(1, 0, 0)));
	mowedVerts_.push_back(tigl::Vertex::PTN(glm::vec3(size.x, size.y, size.z), glm::vec2(0, 1), glm::vec3(1, 0, 0)));
	mowedVerts_.push_back(tigl::Vertex::PTN(glm::vec3(size.x, -size.y, size.z), glm::vec2(0, 0), glm::vec3(1, 0, 0)));

	//right
	mowedVerts_.push_back(tigl::Vertex::PTN(glm::vec3(-size.x, -size.y, -size.z), glm::vec2(0, 0), glm::vec3(-1, 0, 0)));
	mowedVerts_.push_back(tigl::Vertex::PTN(glm::vec3(-size.x, size.y, -size.z), glm::vec2(0, 1), glm::vec3(-1, 0, 0)));
	mowedVerts_.push_back(tigl::Vertex::PTN(glm::vec3(-size.x, size.y, size.z), glm::vec2(1, 1), glm::vec3(-1, 0, 0)));
	mowedVerts_.push_back(tigl::Vertex::PTN(glm::vec3(-size.x, -size.y, size.z), glm::vec2(1, 0), glm::vec3(-1, 0, 0)));

	//back
	mowedVerts_.push_back(tigl::Vertex::PTN(glm::vec3(-size.x, -size.y, -size.z), glm::vec2(0, 0), glm::vec3(0, 0, -1)));
	mowedVerts_.push_back(tigl::Vertex::PTN(glm::vec3(-size.x, size.y, -size.z), glm::vec2(0, 1), glm::vec3(0, 0, -1)));
	mowedVerts_.push_back(tigl::Vertex::PTN(glm::vec3(size.x, size.y, -size.z), glm::vec2(1, 1), glm::vec3(0, 0, -1)));
	mowedVerts_.push_back(tigl::Vertex::PTN(glm::vec3(size.x, -size.y, -size.z), glm::vec2(1, 0), glm::vec3(0, 0, -1)));

	//front
	mowedVerts_.push_back(tigl::Vertex::PTN(glm::vec3(-size.x, -size.y, size.z), glm::vec2(0, 0), glm::vec3(0, 0, 1)));
	mowedVerts_.push_back(tigl::Vertex::PTN(glm::vec3(-size.x, size.y, size.z), glm::vec2(0, 1), glm::vec3(0, 0, 1)));
	mowedVerts_.push_back(tigl::Vertex::PTN(glm::vec3(size.x, size.y, size.z), glm::vec2(1, 1), glm::vec3(0, 0, 1)));
	mowedVerts_.push_back(tigl::Vertex::PTN(glm::vec3(size.x, -size.y, size.z), glm::vec2(1, 0), glm::vec3(0, 0, 1)));
#pragma endregion
}

void LawnTileComponent::draw()
{
	tigl::shader->enableColorMult(true);
	if (selected && !mowed)
		tigl::shader->setColorMult(glm::vec4(0.7f, greenMult_, 0.7f, 1));
	else
		tigl::shader->setColorMult(glm::vec4(0, greenMult_, 0, 1));

	texture_->bind();

	if (mowed)
		tigl::drawVertices(GL_QUADS, unmowedVerts_);
	else
		tigl::drawVertices(GL_QUADS, mowedVerts_);

	texture_->unbind();

	tigl::shader->enableColorMult(false);
}

void LawnTileComponent::onClick(const TileAction action)
{
	switch (action)
	{
	case TILE_ACTION_MOW:
		mowed = true;
		break;
	case TILE_ACTION_FLAG:
		break;
	}
}
