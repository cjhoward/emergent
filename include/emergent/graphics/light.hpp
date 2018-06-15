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

#ifndef EMERGENT_GRAPHICS_LIGHT_HPP
#define EMERGENT_GRAPHICS_LIGHT_HPP

#include <emergent/graphics/scene-object.hpp>

namespace Emergent
{

/**
 * Enumerates light types.
 *
 * @ingroup graphics
 */
enum class LightType
{
	POINT,
	DIRECTIONAL,
	SPOTLIGHT,
	AMBIENT_CUBE
};

/**
 * Abstract base class for light sources.
 *
 * @ingroup graphics
 */
class Light: public SceneObject
{
public:
	/**
	 * Creates an instance of Light.
	 */
	Light();
	
	/**
	 * Destroys an instance of Light.
	 */
	virtual ~Light() = 0;
	
	/// Returns ObjectType::LIGHT
	virtual SceneObjectType getSceneObjectType() const;
	
	/// Returns the light type.
	virtual LightType getLightType() const = 0;
};

inline SceneObjectType Light::getSceneObjectType() const
{
	return SceneObjectType::LIGHT;
}

/**
 * Abstract base class for infinitely small light sources.
 *
 * @ingroup graphics
 */
class PunctualLight: public Light
{
public:
	/**
	 * Destroys an instance of PunctualLight.
	 */
	virtual ~PunctualLight() = 0;

	/**
	 * Sets the light color.
	 *
	 * @param color Specifies the light color.
	 */
	void setColor(const glm::vec3& color);

	/**
	 * Sets the light intensity.
	 *
	 * @param intensity Specifies the light intensity.
	 */
	void setIntensity(float intensity);

	/**
	 * Returns the light color. The initial value is `(1, 1, 1)`.
	 */
	const glm::vec3& getColor() const;
	
	/**
	 * Returns the light intensity. The initial value is `1`.
	 */
	float getIntensity() const;

	/**
	 * Returns the light color multiplied by the light intensity.
	 */
	const glm::vec3& getScaledColor() const;
	
protected:
	/**
	 * Creates an instance of PunctualLight.
	 */
	PunctualLight();

private:
	glm::vec3 color;
	float intensity;
	glm::vec3 scaledColor;
};

inline void PunctualLight::setColor(const glm::vec3& color)
{
	this->color = color;
	this->scaledColor = color * intensity;
}

inline void PunctualLight::setIntensity(float intensity)
{
	this->intensity = intensity;
	this->scaledColor = color * intensity;
}

inline const glm::vec3& PunctualLight::getColor() const
{
	return color;
}

inline float PunctualLight::getIntensity() const
{
	return intensity;
}

inline const glm::vec3& PunctualLight::getScaledColor() const
{
	return scaledColor;
}

/**
 * Omnidirectional point light source.
 *
 * @ingroup graphics
 */
class PointLight: public PunctualLight
{
public:
	/**
	 * Creates an instance of PointLight.
	 */
	PointLight();
	
	/**
	 * Destroys an instance of PointLight.
	 */
	virtual ~PointLight();
	
	/**
	 * Sets the constant, linear, and quadratic attenuation factors. 
	 *
	 * @param attenuation Specifies the attenuation vector.
	 */
	void setAttenuation(const glm::vec3& attenuation);
	
	/// Returns LightType::POINT
	virtual LightType getLightType() const;
	
	/**
	 * Returns the constant, linear, and quadratic attenuation factors.  The initial value is `(1, 0, 0)`.
	 */
	const glm::vec3& getAttenuation() const;
	
private:
	glm::vec3 attenuation;
};

inline void PointLight::setAttenuation(const glm::vec3& attenuation)
{
	this->attenuation = attenuation;
}

inline LightType PointLight::getLightType() const
{
	return LightType::POINT;
}

inline const glm::vec3& PointLight::getAttenuation() const
{
	return attenuation;
}

/**
 * Parallel ray light source.
 *
 * @ingroup graphics
 */
class DirectionalLight: public PunctualLight
{
public:
	/**
	 * Creates an instance of DirectionalLight.
	 */
	DirectionalLight();
	
	/**
	 * Destroys an instance of DirectionalLight.
	 */
	virtual ~DirectionalLight();
	
	/**
	 * Sets the light direction.
	 *
	 * @param direction Specifies the light direction.
	 */
	void setDirection(const glm::vec3& direction);
	
	/// Returns LightType::DIRECTIONAL
	virtual LightType getLightType() const;
	
	/**
	 * Returns the light direction. The initial value is `(0, 0, -1)`.
	 */
	const glm::vec3& getDirection() const;
	
private:
	virtual void transformed();
	
	glm::vec3 direction;
};

inline LightType DirectionalLight::getLightType() const
{
	return LightType::DIRECTIONAL;
}

inline const glm::vec3& DirectionalLight::getDirection() const
{
	return direction;
}

/**
 * Directional cone light source.
 *
 * @ingroup graphics
 */
class Spotlight: public PunctualLight
{
public:
	/**
	 * Creates an instance of Spotlight.
	 */
	Spotlight();
	
	/**
	 * Destroys an instance of Spotlight.
	 */
	~Spotlight();
	
	/**
	 * Sets the constant, linear, and quadratic attenuation factors. 
	 *
	 * @param attenuation Specifies the attenuation vector.
	 */
	void setAttenuation(const glm::vec3& attenuation);
	
	/**
	 * Sets the light direction.
	 *
	 * @param direction Specifies the light direction.
	 */
	void setDirection(const glm::vec3& direction);
	
	/**
	 * Sets the cosine of the maximum spread angle of the spotlight.
	 *
	 * @param cosAngle Specifies the cosine of the cutoff angle.
	 */
	void setCutoff(float cosAngle);
	
	/**
	 * Sets the exponent value that specifies the intensity distribution of the light.
	 *
	 * @param exponent Specifies an exponent value.
	 */
	void setExponent(float exponent);
	
	/// Returns LightType::SPOTLIGHT.
	virtual LightType getLightType() const;
	
	/**
	 * Returns the constant, linear, and quadratic attenuation factors.  The initial value is `(1, 0, 0)`.
	 */
	const glm::vec3& getAttenuation() const;
	
	/**
	 * Returns the light direction. The initial value is `(0, 0, -1)`.
	 */
	const glm::vec3& getDirection() const;
	
	/**
	 * Returns the cosine of the maximum spread angle of the spotlight, in radians. The initial value is Pi.
	 */
	float getCutoff() const;
	
	/** 
	 * Returns the exponent value that specifies the intensity distribution of the light. The initial value is `0`.
	 */
	float getExponent() const;
	
private:
	virtual void transformed();

	glm::vec3 attenuation;	
	glm::vec3 direction;
	float cutoff;
	float exponent;
};

inline void Spotlight::setAttenuation(const glm::vec3& attenuation)
{
	this->attenuation = attenuation;
}

inline void Spotlight::setCutoff(float cosAngle)
{
	this->cutoff = cosAngle;
}

inline void Spotlight::setExponent(float exponent)
{
	this->exponent = exponent;
}

inline LightType Spotlight::getLightType() const
{
	return LightType::SPOTLIGHT;
}

inline const glm::vec3& Spotlight::getAttenuation() const
{
	return attenuation;
}

inline const glm::vec3& Spotlight::getDirection() const
{
	return direction;
}

inline float Spotlight::getCutoff() const
{
	return cutoff;
}

inline float Spotlight::getExponent() const
{
	return exponent;
}

} // namespace Emergent

#endif // EMERGENT_GRAPHICS_LIGHT_HPP

