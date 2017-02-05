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

#ifndef EMERGENT_GRAPHICS_MATERIAL_HPP
#define EMERGENT_GRAPHICS_MATERIAL_HPP

#include <emergent/math/types.hpp>

namespace Emergent
{

/**
 * Abstract base class for materials.
 *
 * @ingroup graphics
 */
class Material
{
public:
	/**
	 * Destroys an instance of Material.
	 */
	virtual ~Material() = 0;
	
	/**
	 * Returns the ID of the material format.
	 */
	virtual unsigned int getMaterialFormatID() const = 0;
};

/**
 * Default material
 */
class DefaultMaterial: public Material
{
public:
	/// Returns ~0
	virtual unsigned int getMaterialFormatID() const;
	
	Vector3 diffuseColor;
	Vector3 specularColor;
	Vector3 emissiveColor;
	float hardness;
	float opacity;
	bool shadeless;
	bool shadowCaster;
	bool shadowReceiver;
};

inline unsigned int DefaultMaterial::getMaterialFormatID() const
{
	return ~((unsigned int)0);
}

} // namespace Emergent

#endif // EMERGENT_GRAPHICS_MATERIAL_HPP
