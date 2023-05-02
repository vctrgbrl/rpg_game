#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <SDL2/SDL_image.h>
#include <iostream>
#include "glad/glad.h"
#include "Texture.hpp"

using namespace Lone;

Texture::Texture(const char* filePath) :
	width(0), height(0), nrChannels(0)
{
	glGenTextures(1, &id);
	std::cout << id << std::endl;
	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load(filePath, &width, &height, &nrChannels, 4);
	std::cout << width << std::endl;
	std::cout << height << std::endl;
	std::cout << nrChannels << std::endl;
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(data);
	}
	else
	{
		std::cout << "Failed to load texture: " << filePath << std::endl;
	}
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture() {
	glDeleteTextures(1, &id);
}

void Texture::Bind(uint32_t slot) {
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, id);
}