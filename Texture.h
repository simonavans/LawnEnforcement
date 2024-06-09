#pragma once
#include <string>
#include <GL/glew.h>

class Texture
{
	GLuint textureId;
public:
	int textureWidth;
	int textureHeight;

	Texture(const std::string& fileName);
	void bind() const;
	static void unbind();
};

