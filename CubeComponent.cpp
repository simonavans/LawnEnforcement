#include "CubeComponent.h"

#include "Texture.h"

CubeComponent::CubeComponent(const glm::vec3& size, const std::shared_ptr<Texture>& texture)
{
	this->texture_ = texture;

	//bottom
	verts_.push_back(tigl::Vertex::PTN(glm::vec3(-size.x, -size.y, -size.z), glm::vec2(0, 0), glm::vec3(0, -1, 0)));
	verts_.push_back(tigl::Vertex::PTN(glm::vec3(size.x, -size.y, -size.z), glm::vec2(1, 0), glm::vec3(0, -1, 0)));
	verts_.push_back(tigl::Vertex::PTN(glm::vec3(size.x, -size.y, size.z), glm::vec2(1, 1), glm::vec3(0, -1, 0)));
	verts_.push_back(tigl::Vertex::PTN(glm::vec3(-size.x, -size.y, size.z), glm::vec2(0, 1), glm::vec3(0, -1, 0)));

	//top
	verts_.push_back(tigl::Vertex::PTN(glm::vec3(-size.x, size.y, -size.z), glm::vec2(0, 0), glm::vec3(0, 1, 0)));
	verts_.push_back(tigl::Vertex::PTN(glm::vec3(size.x, size.y, -size.z), glm::vec2(1, 0), glm::vec3(0, 1, 0)));
	verts_.push_back(tigl::Vertex::PTN(glm::vec3(size.x, size.y, size.z), glm::vec2(1, 1), glm::vec3(0, 1, 0)));
	verts_.push_back(tigl::Vertex::PTN(glm::vec3(-size.x, size.y, size.z), glm::vec2(0, 1), glm::vec3(0, 1, 0)));

	//left
	verts_.push_back(tigl::Vertex::PTN(glm::vec3(size.x, -size.y, -size.z), glm::vec2(1, 0), glm::vec3(1, 0, 0)));
	verts_.push_back(tigl::Vertex::PTN(glm::vec3(size.x, size.y, -size.z), glm::vec2(1, 1), glm::vec3(1, 0, 0)));
	verts_.push_back(tigl::Vertex::PTN(glm::vec3(size.x, size.y, size.z), glm::vec2(0, 1), glm::vec3(1, 0, 0)));
	verts_.push_back(tigl::Vertex::PTN(glm::vec3(size.x, -size.y, size.z), glm::vec2(0, 0), glm::vec3(1, 0, 0)));

	//right
	verts_.push_back(tigl::Vertex::PTN(glm::vec3(-size.x, -size.y, -size.z), glm::vec2(0, 0), glm::vec3(-1, 0, 0)));
	verts_.push_back(tigl::Vertex::PTN(glm::vec3(-size.x, size.y, -size.z), glm::vec2(0, 1), glm::vec3(-1, 0, 0)));
	verts_.push_back(tigl::Vertex::PTN(glm::vec3(-size.x, size.y, size.z), glm::vec2(1, 1), glm::vec3(-1, 0, 0)));
	verts_.push_back(tigl::Vertex::PTN(glm::vec3(-size.x, -size.y, size.z), glm::vec2(1, 0), glm::vec3(-1, 0, 0)));

	//back
	verts_.push_back(tigl::Vertex::PTN(glm::vec3(-size.x, -size.y, -size.z), glm::vec2(0, 0), glm::vec3(0, 0, -1)));
	verts_.push_back(tigl::Vertex::PTN(glm::vec3(-size.x, size.y, -size.z), glm::vec2(0, 1), glm::vec3(0, 0, -1)));
	verts_.push_back(tigl::Vertex::PTN(glm::vec3(size.x, size.y, -size.z), glm::vec2(1, 1), glm::vec3(0, 0, -1)));
	verts_.push_back(tigl::Vertex::PTN(glm::vec3(size.x, -size.y, -size.z), glm::vec2(1, 0), glm::vec3(0, 0, -1)));

	//front
	verts_.push_back(tigl::Vertex::PTN(glm::vec3(-size.x, -size.y, size.z), glm::vec2(0, 0), glm::vec3(0, 0, 1)));
	verts_.push_back(tigl::Vertex::PTN(glm::vec3(-size.x, size.y, size.z), glm::vec2(0, 1), glm::vec3(0, 0, 1)));
	verts_.push_back(tigl::Vertex::PTN(glm::vec3(size.x, size.y, size.z), glm::vec2(1, 1), glm::vec3(0, 0, 1)));
	verts_.push_back(tigl::Vertex::PTN(glm::vec3(size.x, -size.y, size.z), glm::vec2(1, 0), glm::vec3(0, 0, 1)));
}

CubeComponent::CubeComponent(const glm::vec3& size, const glm::vec4& color)
{
	this->texture_ = nullptr;

	//bottom
	verts_.push_back(tigl::Vertex::PC(glm::vec3(-size.x, -size.y, -size.z), color));
	verts_.push_back(tigl::Vertex::PC(glm::vec3(size.x, -size.y, -size.z), color));
	verts_.push_back(tigl::Vertex::PC(glm::vec3(size.x, -size.y, size.z), color));
	verts_.push_back(tigl::Vertex::PC(glm::vec3(-size.x, -size.y, size.z), color));

	//top
	verts_.push_back(tigl::Vertex::PC(glm::vec3(-size.x, size.y, -size.z), color));
	verts_.push_back(tigl::Vertex::PC(glm::vec3(size.x, size.y, -size.z), color));
	verts_.push_back(tigl::Vertex::PC(glm::vec3(size.x, size.y, size.z), color));
	verts_.push_back(tigl::Vertex::PC(glm::vec3(-size.x, size.y, size.z), color));

	//left
	verts_.push_back(tigl::Vertex::PC(glm::vec3(size.x, -size.y, -size.z), color));
	verts_.push_back(tigl::Vertex::PC(glm::vec3(size.x, size.y, -size.z), color));
	verts_.push_back(tigl::Vertex::PC(glm::vec3(size.x, size.y, size.z), color));
	verts_.push_back(tigl::Vertex::PC(glm::vec3(size.x, -size.y, size.z), color));

	//right
	verts_.push_back(tigl::Vertex::PC(glm::vec3(-size.x, -size.y, -size.z), color));
	verts_.push_back(tigl::Vertex::PC(glm::vec3(-size.x, size.y, -size.z), color));
	verts_.push_back(tigl::Vertex::PC(glm::vec3(-size.x, size.y, size.z), color));
	verts_.push_back(tigl::Vertex::PC(glm::vec3(-size.x, -size.y, size.z), color));

	//back
	verts_.push_back(tigl::Vertex::PC(glm::vec3(-size.x, -size.y, -size.z), color));
	verts_.push_back(tigl::Vertex::PC(glm::vec3(-size.x, size.y, -size.z), color));
	verts_.push_back(tigl::Vertex::PC(glm::vec3(size.x, size.y, -size.z), color));
	verts_.push_back(tigl::Vertex::PC(glm::vec3(size.x, -size.y, -size.z), color));

	//front
	verts_.push_back(tigl::Vertex::PC(glm::vec3(-size.x, -size.y, size.z), color));
	verts_.push_back(tigl::Vertex::PC(glm::vec3(-size.x, size.y, size.z), color));
	verts_.push_back(tigl::Vertex::PC(glm::vec3(size.x, size.y, size.z), color));
	verts_.push_back(tigl::Vertex::PC(glm::vec3(size.x, -size.y, size.z), color));
}

void CubeComponent::draw()
{
	if (texture_)
		texture_->bind();
	else
		tigl::shader->enableColor(true);

	tigl::drawVertices(GL_QUADS, verts_);

	if (texture_)
		texture_->unbind();
	else
		tigl::shader->enableColor(false);
}
