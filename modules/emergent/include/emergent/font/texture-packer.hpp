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

#ifndef EMERGENT_FONT_TEXTURE_PACKER_HPP
#define EMERGENT_FONT_TEXTURE_PACKER_HPP

#include <emergent/geometry/rect.hpp>
#include <cstdlib>
#include <map>
#include <string>

namespace Emergent
{

class TexturePacker;

/**
 * Texture packer binary tree node.
 *
 * @ingroup font
 */
class TexturePackerNode
{
public:
	/**
	 * Returns bounds describing the position of a texture.
	 *
	 * @return Bounds of the position of a texture.
	 */
	const Rect& getBounds() const;
	
private:
	friend class TexturePacker;
	
	/**
	 * Creates an instance of TexturePackerNode.
	 */
	TexturePackerNode();
	
	/**
	 * Destroys an instance of TexturePackerNode.
	 */
	~TexturePackerNode();
	
	/**
	 * Inserts a texture into the tree.
	 *
	 * @param width Specifies the width of the texture.
	 * @param height Specifies the height of the texture.
	 * @return Pointer to the node containing the inserted texture, or `nullptr` if the texture could not be inserted.
	 */
	TexturePackerNode* insert(float width, float height);
	
	TexturePackerNode* children[2];
	Rect bounds;
	bool reserved;
};

inline TexturePackerNode::TexturePackerNode()
{
	children[0] = nullptr;
	children[1] = nullptr;
	reserved = false;
}

inline TexturePackerNode::~TexturePackerNode()
{
	delete children[0];
	delete children[1];
}

inline const Rect& TexturePackerNode::getBounds() const
{
	return bounds;
}

/**
 * Packs textures for optimal insertion into a texture atlas.
 *
 * @see http://www.blackpawn.com/texts/lightmaps/
 *
 * @ingroup font
 */
class TexturePacker
{
public:
	/**
	 * Creates texture packer.
	 *
	 * @param bounds Texture packing bounds.
	 */
	TexturePacker(const Rect& bounds);
	
	/**
	 * Destroys a texture packer.
	 */
	~TexturePacker();
	
	/**
	 * Packs a texture.
	 *
	 * @param width Specifies the width of the texture.
	 * @param height Specifies the height of the texture.
	 * @return Pointer to the node containing the packed texture, or `nullptr` if the texture could not be packed.
	 */
	const TexturePackerNode* pack(float width, float height);
	
	/**
	 * Removes all textures from the packer.
	 */
	void clear();

	/**
	 * Returns the texture packing bounds.
	 *
	 * @return Texture packing bounds.
	 */
	const Rect& getBounds() const;
	
private:
	TexturePackerNode root;
};

inline const Rect& TexturePacker::getBounds() const
{
	return root.bounds;
}

} // namespace Emergent

#endif // EMERGENT_FONT_TEXTURE_PACKER_HPP
