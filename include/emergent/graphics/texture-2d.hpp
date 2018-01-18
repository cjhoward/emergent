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

#ifndef EMERGENT_GRAPHICS_TEXTURE_2D_HPP
#define EMERGENT_GRAPHICS_TEXTURE_2D_HPP

#include <emergent/graphics/gl3w.hpp>

namespace Emergent
{

/**
 * A 2D texture which can be uploaded to a shader via shader inputs.
 *
 * @ingroup graphics
 */
class Texture2D
{
public:
	/**
	 * Creates a 2D texture.
	 */
	Texture2D();
	
	/**
	 * Destroys a 2D texture.
	 */
	~Texture2D();
	
	/**
	 * Destroys the texture.
	 */
	void destroy();
	
	/**
	 * Sets the OpenGL texture ID.
	 *
	 * @param textureID OpenGL texture ID.
	 */
	void setTextureID(GLuint textureID);
	
	/**
	 * Sets the width of the texture.
	 *
	 * @param width Width of the texture in pixels.
	 */
	void setWidth(int width);
	
	/**
	 * Sets the height of the texture.
	 *
	 * @param height Height of the texture in pixels.
	 */
	void setHeight(int height);
	
	/**
	 * Returns the OpenGL texture ID
	 */
	GLuint getTextureID() const;
	
	/**
	 * Returns the width of the texture in pixels.
	 */
	int getWidth() const;
	
	/**
	 * Returns the height of the texture in pixels.
	 */
	int getHeight() const;
	
private:
	GLuint textureID;
	int width;
	int height;
};

inline GLuint Texture2D::getTextureID() const
{
	return textureID;
}

inline int Texture2D::getWidth() const
{
	return width;
}

inline int Texture2D::getHeight() const
{
	return height;
}

} // namespace Emergent

#endif // EMERGENT_GRAPHICS_TEXTURE_2D_HPP
