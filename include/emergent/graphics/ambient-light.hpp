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
	virtual ~AmbientLight() = 0;
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
	~AmbientCube();
	
	/// Returns LightType::AMBIENT_CUBE
	virtual LightType getLightType() const;
	
	/**
	 * Sets the diffuse cubemap texture.
	 */
	void setDiffuseTexture(const TextureCube* texture);
	
	/**
	 * Sets the specular cubemap texture
	 */
	void setSpecularTexture(const TextureCube* texture);
	
	/**
	 * Returns the diffuse cubemap texture.
	 */
	const TextureCube* getDiffuseTexture() const;
	
	/**
	 * Returns the specular cubemap texture.
	 */
	const TextureCube* getSpecularTexture() const;

private:
	const TextureCube* diffuseTexture;
	const TextureCube* specularTexture;
};

inline void AmbientCube::setDiffuseTexture(const TextureCube* texture)
{
	this->diffuseTexture = texture;
}

inline void AmbientCube::setSpecularTexture(const TextureCube* texture)
{
	this->specularTexture = texture;
}

inline LightType AmbientCube::getLightType() const
{
	return LightType::AMBIENT_CUBE;
}

inline const TextureCube* AmbientCube::getDiffuseTexture() const
{
	return diffuseTexture;
}

inline const TextureCube* AmbientCube::getSpecularTexture() const
{
	return specularTexture;
}

} // namespace Emergent

#endif // EMERGENT_GRAPHICS_AMBIENT_LIGHT_HPP
