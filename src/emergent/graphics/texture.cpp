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
