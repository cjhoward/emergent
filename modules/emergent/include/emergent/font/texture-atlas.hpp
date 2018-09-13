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

#ifndef EMERGENT_FONT_TEXTURE_ATLAS_HPP
#define EMERGENT_FONT_TEXTURE_ATLAS_HPP

#include <emergent/geometry/rect.hpp>
#include <map>
#include <string>

namespace Emergent
{

/**
 * An atlas of texures.
 *
 * @ingroup font
 */
class TextureAtlas
{
public:
	/**
	 * Inserts a texture into the atlas.
	 *
	 * @param name Name of the texture to insert.
	 * @param bounds Bounds of the texture.
	 */
	void insert(const std::string& name, const Rect& bounds);

	/**
	 * Removes a texture from the atlas.
	 *
	 * @param name Name of the texture to remove.
	 */
	void remove(const std::string& name);

	/**
	 * Removes all textures from the atlas.
	 */
	void clear();

	/**
	 * Returns whether or not a texture is in the atlas.
	 *
	 * @param name Name of a texture.
	 * @return true if the texture is in the atlas, false otherwise.
	 */
	bool hasTexture(const std::string& name) const;

	/**
	 * Returns the bounds of a texture in the atlas.
	 *
	 * @param name Name of the texture.
	 * @return Bounds of the texture.
	 *
	 * @throw std::runtime_error Missing texture.
	 */
	const Rect& getBounds(const std::string& name) const;

private:
	std::map<std::string, Rect> atlas;
};

} // namespace Emergent

#endif // EMERGENT_FONT_TEXTURE_ATLAS_HPP
