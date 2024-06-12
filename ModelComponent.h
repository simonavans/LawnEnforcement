#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <string>
#include <vector>
#include <list>

#include "DrawComponent.h"

class Texture;

class ModelComponent : public DrawComponent
{
	class Vertex
	{
	public:
		int position;
		int normal;
		int texcoord; 
	};

	class Face
	{
	public:
		std::list<Vertex> vertices;
	};
	class MaterialInfo
	{
	public:
		MaterialInfo();
		std::string name;
		Texture* texture;
	};

	class ObjGroup
	{
	public:
		std::string name;
		int materialIndex;
		std::list<Face> faces;
	};

	std::vector<glm::vec3> vertices_;
	std::vector<glm::vec3> normals_;
	std::vector<glm::vec2> texcoords_;
	std::vector<ObjGroup*> groups_;
	std::vector<MaterialInfo*> materials_;

	void loadMaterialFile(const std::string &fileName, const std::string &dirName);
public:
	ModelComponent(const std::string &fileName);

	void draw() override;
};

