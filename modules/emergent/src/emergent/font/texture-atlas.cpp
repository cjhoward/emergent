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

#include <emergent/font/texture-atlas.hpp>
#include <stdexcept>

namespace Emergent
{

void TextureAtlas::insert(const std::string& name, const Rect& bounds)
{
	atlas[name] = bounds;
}

void TextureAtlas::remove(const std::string& name)
{
	auto it = atlas.find(name);
	if (it != atlas.end())
	{
		atlas.erase(it);
	}
}

void TextureAtlas::clear()
{
	atlas.clear();
}

bool TextureAtlas::hasTexture(const std::string& name) const
{
	auto it = atlas.find(name);
	return (it != atlas.end());
}

const Rect& TextureAtlas::getBounds(const std::string& name) const
{
	auto it = atlas.find(name);
	if (it != atlas.end())
	{
		return it->second;
	}
	else
	{
		std::string error = std::string("TextureAtlas::getBounds(): Missing texture: \"") + name + std::string("\"");
		throw std::runtime_error(error.c_str());
	}
}

} // namespace Emergent
