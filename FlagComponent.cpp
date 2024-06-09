#include "FlagComponent.h"

#include "tigl.h"
#include "glm/vec3.hpp"

FlagComponent::FlagComponent()
{
	constexpr int length = 1;
	constexpr int width = 0.01f;
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

void FlagComponent::draw()
{
	
}

