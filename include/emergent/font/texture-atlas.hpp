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

#ifndef EMERGENT_FONT_TEXTURE_ATLAS_HPP
#define EMERGENT_FONT_TEXTURE_ATLAS_HPP

#include <emergent/geometry/rect.hpp>
#include <cstdlib>

namespace Emergent
{

class TextureAtlas;

/**
 * Texture atlas binary tree node.
 *
 * @ingroup font
 */
class TextureAtlasNode
{
public:
	/**
	 * Returns bounds describing the position of a texture.
	 *
	 * @return Bounds of the position of a texture.
	 */
	const Rect& getBounds() const;
	
private:
	friend class TextureAtlas;
	
	/**
	 * Creates an instance of TextureAtlasNode.
	 */
	TextureAtlasNode();
	
	/**
	 * Destroys an instance of TextureAtlasNode.
	 */
	~TextureAtlasNode();
	
	/**
	 * Inserts a texture into the tree.
	 *
	 * @param width Specifies the width of the texture.
	 * @param height Specifies the height of the texture.
	 * @return Pointer to the node containing the inserted texture, or `nullptr` if the texture could not be inserted.
	 */
	TextureAtlasNode* insert(unsigned int width, unsigned int height);
	
	TextureAtlasNode* children[2];
	Rect bounds;
	bool reserved;
};

inline TextureAtlasNode::TextureAtlasNode()
{
	children[0] = nullptr;
	children[1] = nullptr;
	reserved = false;
}

inline TextureAtlasNode::~TextureAtlasNode()
{
	delete children[0];
	delete children[1];
}

inline const Rect& TextureAtlasNode::getBounds() const
{
	return bounds;
}

/**
 * Manages subtextures.
 *
 * @see http://www.blackpawn.com/texts/lightmaps/
 *
 * @ingroup font
 */
class TextureAtlas
{
public:
	/**
	 * Creates an instance of TextureAtlas.
	 *
	 * @param width Specifies the width of the texture atlas.
	 * @param height Specifies the height of the texture atlas.
	 */
	TextureAtlas(unsigned int width, unsigned int height);
	
	/**
	 * Destroys an instance of TextureAtlas.
	 */
	~TextureAtlas();
	
	/**
	 * Inserts a texture into the atlas.
	 *
	 * @param width Specifies the width of the texture.
	 * @param height Specifies the height of the texture.
	 * @return Pointer to the node containing the inserted texture, or `nullptr` if the texture could not be inserted.
	 */
	const TextureAtlasNode* insert(unsigned int width, unsigned int height);
	
	/**
	 * Removes all textures from the atlas.
	 */
	void clear();
	
	/**
	 * Returns the width of the texture atlas.
	 *
	 * @return Width of the texture atlas.
	 */
	unsigned int getWidth() const;
	
	/**
	 * Returns the height of the texture atlas.
	 *
	 * @return Height of the texture atlas.
	 */
	unsigned int getHeight() const;
	
private:
	unsigned int width;
	unsigned int height;
	TextureAtlasNode root;
};

inline unsigned int TextureAtlas::getWidth() const
{
	return width;
}

inline unsigned int TextureAtlas::getHeight() const
{
	return height;
}

} // namespace Emergent

#endif // EMERGENT_FONT_TEXTURE_ATLAS_HPP
