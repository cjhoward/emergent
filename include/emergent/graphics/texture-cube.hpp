/*
 * Copyright (C) 2017-2018  Christopher J. Howard
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

#ifndef EMERGENT_GRAPHICS_TEXTURE_CUBE_HPP
#define EMERGENT_GRAPHICS_TEXTURE_CUBE_HPP

#include <emergent/graphics/gl3w.hpp>

namespace Emergent
{

/**
 * A cube texture which can be uploaded to a shader via shader inputs.
 *
 * @ingroup graphics
 */
class TextureCube
{
public:
	/**
	 * Creates a cube texture.
	 */
	TextureCube();
	
	/**
	 * Destroys a cube texture.
	 */
	~TextureCube();
	
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
	 * Sets the size of the cube face.
	 *
	 * @param size Size of the cube face in pixels.
	 */
	void setFaceSize(int size);
	
	/**
	 * Returns the OpenGL texture ID
	 */
	GLuint getTextureID() const;
	
	/**
	 * Returns the size of the cube face in pixels.
	 */
	int getFaceSize() const;
	
private:
	GLuint textureID;
	int faceSize;
};

inline GLuint TextureCube::getTextureID() const
{
	return textureID;
}

inline int TextureCube::getFaceSize() const
{
	return faceSize;
}

} // namespace Emergent

#endif // EMERGENT_GRAPHICS_TEXTURE_CUBE_HPP
