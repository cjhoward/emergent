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

#ifndef EMERGENT_GRAPHICS_TEXTURE_HPP
#define EMERGENT_GRAPHICS_TEXTURE_HPP

#include <emergent/graphics/gl3w.hpp>
#include <string>

namespace Emergent
{

/**
 * 
 *
 * @ingroup graphics
 */
class Texture
{
public:
	Texture();
	~Texture();
	
	void destroy();
	
	void setTextureID(GLuint textureID);
	void setWidth(int width);
	void setHeight(int height);
	
	GLuint getTextureID() const;
	int getWidth() const;
	int getHeight() const;
	
private:
	GLuint textureID;
	int width;
	int height;
};

inline GLuint Texture::getTextureID() const
{
	return textureID;
}

inline int Texture::getWidth() const
{
	return width;
}

inline int Texture::getHeight() const
{
	return height;
}

} // namespace Emergent

#endif // EMERGENT_GRAPHICS_TEXTURE_HPP
