/*
 * Copyright (C) 2017-2019  Christopher J. Howard
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

#ifndef EMERGENT_GRAPHICS_AMBIENT_LIGHT_HPP
#define EMERGENT_GRAPHICS_AMBIENT_LIGHT_HPP

#include <emergent/graphics/light.hpp>

namespace Emergent
{

class TextureCube;

/**
 * Abstract base class for ambient light sources.
 *
 * @ingroup graphics
 */
class AmbientLight: public Light
{
public:
	/// Destroys an instance of AmbientLight.
	virtual ~AmbientLight() = default;
};

/**
 * An ambient light which is represented by cubemap textures.
 *
 * @ingroup graphics
 */
class AmbientCube: public AmbientLight
{
public:
	/**
	 * Creates an instance of AmbientCube.
	 */
	AmbientCube();
	
	/**
	 * Destroys an instance of AmbientCube.
	 */
	virtual ~AmbientCube();
	
	/// Returns LightType::AMBIENT_CUBE
	virtual LightType getLightType() const;
	
	/**
	 * Sets the irradiance cubemap texture.
	 */
	void setIrradianceMap(const TextureCube* texture);
	
	/**
	 * Sets the radiance cubemap texture
	 */
	void setRadianceMap(const TextureCube* texture);
	
	/**
	 * Returns the irradiance cubemap texture.
	 */
	const TextureCube* getIrradianceMap() const;
	
	/**
	 * Returns the radiance cubemap texture.
	 */
	const TextureCube* getRadianceMap() const;

private:
	const TextureCube* irradianceMap;
	const TextureCube* radianceMap;
};

inline void AmbientCube::setIrradianceMap(const TextureCube* texture)
{
	this->irradianceMap = texture;
}

inline void AmbientCube::setRadianceMap(const TextureCube* texture)
{
	this->radianceMap = texture;
}

inline LightType AmbientCube::getLightType() const
{
	return LightType::AMBIENT_CUBE;
}

inline const TextureCube* AmbientCube::getIrradianceMap() const
{
	return irradianceMap;
}

inline const TextureCube* AmbientCube::getRadianceMap() const
{
	return radianceMap;
}

} // namespace Emergent

#endif // EMERGENT_GRAPHICS_AMBIENT_LIGHT_HPP
