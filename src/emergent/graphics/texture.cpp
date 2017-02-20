/*
 * Copyright (C) 2017  Christopher J. Howard
 *
 * This file is part of Emergent.
 *
 * Emergent is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Emergent is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Emergent.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <emergent/graphics/texture.hpp>
#include <emergent/graphics/material.hpp>
#include <emergent/graphics/stb-image.hpp>
#include <iostream>

namespace Emergent
{

/// @todo remove this hack
#define GL_TEXTURE_MAX_ANISOTROPY_EXT 0x84FE
#define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT 0x84FF

Texture::Texture():
	textureID(0),
	width(0),
	height(0)
{}

Texture::~Texture()
{
	destroy();
}

void Texture::destroy()
{
	if (textureID != 0)
	{
		glDeleteTextures(1, &textureID);
		
		textureID = 0;
		width = 0;
		height = 0;
	}
}

bool Texture::load(const std::string& filename)
{
	destroy();
	
	int components;
	
	// Load image data
	stbi_set_flip_vertically_on_load(true);
	unsigned char* pixels = stbi_load(filename.c_str(), &width, &height, &components, 4);
	if (!pixels)
	{
		std::cerr << "Failed to load image \"" << filename << "\"\n";
		return false;
	}
	
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
	glGenerateMipmap(GL_TEXTURE_2D);
	
	// Free loaded image
	stbi_image_free(pixels);
	
	return true;
}

bool Texture::loadCubemap(const std::string& filename)
{
	destroy();

	int components;
	
	// Load image data
	unsigned char* pixels = stbi_load(filename.c_str(), &width, &height, &components, 3);
	if (!pixels)
	{
		std::cerr << "Failed to load image \"" << filename << "\"\n";
		return false;
	}
	
	int faceSize = height >> 1;
	unsigned char* facePixels = new unsigned char[faceSize * faceSize * 3];
	
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	
	int faceIndex = 0;
	GLuint faceMapping[] =
	{
		GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
		GL_TEXTURE_CUBE_MAP_POSITIVE_X,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
		GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
		GL_TEXTURE_CUBE_MAP_POSITIVE_Z
	};
	
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			for (int y = 0; y < faceSize; ++y)
			{
				for (int x = 0; x < faceSize; ++x)
				{
					int index0 = y * faceSize * 3 + x * 3;
					int index1 = (y + i * faceSize) * width * 3 + x * 3 + j * faceSize * 3;
					
					facePixels[index0] = pixels[index1];
					facePixels[index0+1] = pixels[index1+1];
					facePixels[index0+2] = pixels[index1+2];
				}
			}
			
			glTexImage2D(faceMapping[faceIndex++], 0, GL_RGBA, faceSize, faceSize, 0, GL_RGB, GL_UNSIGNED_BYTE, facePixels);
		}
	}
	
	delete[] facePixels;
	
	// Free loaded image
	stbi_image_free(pixels);
	
	return true;
}

void Texture::setTextureID(GLuint textureID)
{
	this->textureID = textureID;
}

void Texture::setWidth(int width)
{
	this->width = width;
}

void Texture::setHeight(int height)
{
	this->height = height;
}

} // namespace Emergent
