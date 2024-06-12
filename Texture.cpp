#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <iostream>

#include "stb_image.h"
#include "tigl.h"

Texture::Texture(const std::string& fileName)
{
	int bpp;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(fileName.c_str(), &textureWidth, &textureHeight, &bpp, 4);
	if (!data)
	{
		std::cout << "Could not load " << fileName.c_str() << ", reason: " << stbi_failure_reason() << '\n';
		exit(0);
	}
	std::cout << "Loaded texture " << fileName.c_str() << '\n';

	glGenTextures(1, &textureId_);
	glBindTexture(GL_TEXTURE_2D, textureId_);
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RGBA,
		textureWidth,
		textureHeight,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		data
	);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(data);
}

void Texture::bind() const
{
	tigl::shader->enableTexture(true);
	glBindTexture(GL_TEXTURE_2D, textureId_);
}

void Texture::unbind()
{
	tigl::shader->enableTexture(false);
	glBindTexture(GL_TEXTURE_2D, 0);
}
