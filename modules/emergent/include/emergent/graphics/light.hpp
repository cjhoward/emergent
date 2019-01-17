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

#include <emergent/animation/tween.hpp>
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
	void setColor(const Vector3& color);

	/**
	 * Sets the light intensity.
	 *
	 * @param intensity Specifies the light intensity.
	 */
	void setIntensity(float intensity);

	/**
	 * Returns the light color. The initial value is `(1, 1, 1)`.
	 */
	const Vector3& getColor() const;
	
	/**
	 * Returns the light intensity. The initial value is `1`.
	 */
	float getIntensity() const;

	/**
	 * Returns the light color multiplied by the light intensity.
	 */
	const Vector3& getScaledColor() const;

	/// Returns the color tween
	const Tween<Vector3>* getColorTween() const;

	/// @copydoc PunctualLight::getColorTween() const
	Tween<Vector3>* getColorTween();
	
	/// Returns the intensity tween
	const Tween<float>* getIntensityTween() const;

	/// @copydoc PunctualLight::getIntensityTween() const
	Tween<float>* getIntensityTween();
	
protected:
	/**
	 * Creates an instance of PunctualLight.
	 */
	PunctualLight();

private:
	Vector3 color;
	float intensity;
	Vector3 scaledColor;
	Tween<Vector3> colorTween;
	Tween<float> intensityTween;
};

inline void PunctualLight::setColor(const Vector3& color)
{
	this->color = color;
	this->scaledColor = color * intensity;
}

inline void PunctualLight::setIntensity(float intensity)
{
	this->intensity = intensity;
	this->scaledColor = color * intensity;
}

inline const Vector3& PunctualLight::getColor() const
{
	return color;
}

inline float PunctualLight::getIntensity() const
{
	return intensity;
}

inline const Vector3& PunctualLight::getScaledColor() const
{
	return scaledColor;
}

inline const Tween<Vector3>* PunctualLight::getColorTween() const
{
	return &colorTween;
}

inline Tween<Vector3>* PunctualLight::getColorTween()
{
	return &colorTween;
}
	
inline const Tween<float>* PunctualLight::getIntensityTween() const
{
	return &intensityTween;
}

inline Tween<float>* PunctualLight::getIntensityTween()
{
	return &intensityTween;
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
	void setAttenuation(const Vector3& attenuation);
	
	/// Returns LightType::POINT
	virtual LightType getLightType() const;
	
	/**
	 * Returns the constant, linear, and quadratic attenuation factors.  The initial value is `(1, 0, 0)`.
	 */
	const Vector3& getAttenuation() const;

	/// Returns the attenuation tween
	const Tween<Vector3>* getAttenuationTween() const;

	/// @copydoc PointLight::getAttenuationTween() const
	Tween<Vector3>* getAttenuationTween();
	
private:
	Vector3 attenuation;
	Tween<Vector3> attenuationTween;
};

inline void PointLight::setAttenuation(const Vector3& attenuation)
{
	this->attenuation = attenuation;
}

inline LightType PointLight::getLightType() const
{
	return LightType::POINT;
}

inline const Vector3& PointLight::getAttenuation() const
{
	return attenuation;
}

inline const Tween<Vector3>* PointLight::getAttenuationTween() const
{
	return &attenuationTween;
}

inline Tween<Vector3>* PointLight::getAttenuationTween()
{
	return &attenuationTween;
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
	void setDirection(const Vector3& direction);
	
	/// Returns LightType::DIRECTIONAL
	virtual LightType getLightType() const;
	
	/**
	 * Returns the light direction. The initial value is `(0, 0, -1)`.
	 */
	const Vector3& getDirection() const;

	/// Returns the direction tween
	const Tween<Vector3>* getDirectionTween() const;

	/// @copydoc DirectionalLight::getDirectionTween() const
	Tween<Vector3>* getDirectionTween();
	
private:
	virtual void transformed();
	
	Vector3 direction;
	Tween<Vector3> directionTween;
};

inline LightType DirectionalLight::getLightType() const
{
	return LightType::DIRECTIONAL;
}

inline const Vector3& DirectionalLight::getDirection() const
{
	return direction;
}

inline const Tween<Vector3>* DirectionalLight::getDirectionTween() const
{
	return &directionTween;
}

inline Tween<Vector3>* DirectionalLight::getDirectionTween()
{
	return &directionTween;
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
	virtual ~Spotlight();
	
	/**
	 * Sets the constant, linear, and quadratic attenuation factors. 
	 *
	 * @param attenuation Specifies the attenuation vector.
	 */
	void setAttenuation(const Vector3& attenuation);
	
	/**
	 * Sets the light direction.
	 *
	 * @param direction Specifies the light direction.
	 */
	void setDirection(const Vector3& direction);
	
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
	const Vector3& getAttenuation() const;
	
	/**
	 * Returns the light direction. The initial value is `(0, 0, -1)`.
	 */
	const Vector3& getDirection() const;
	
	/**
	 * Returns the cosine of the maximum spread angle of the spotlight, in radians. The initial value is Pi.
	 */
	float getCutoff() const;
	
	/** 
	 * Returns the exponent value that specifies the intensity distribution of the light. The initial value is `0`.
	 */
	float getExponent() const;

	/// Returns the attenuation tween
	const Tween<Vector3>* getAttenuationTween() const;

	/// @copydoc Spotlight::getAttenuationTween() const
	Tween<Vector3>* getAttenuationTween();

	/// Returns the direction tween
	const Tween<Vector3>* getDirectionTween() const;

	/// @copydoc Spotlight::getDirectionTween() const
	Tween<Vector3>* getDirectionTween();

	/// Returns the cutoff tween
	const Tween<float>* getCutoffTween() const;

	/// @copydoc Spotlight::getCutoffTween() const
	Tween<float>* getCutoffTween();

	/// Returns the exponent tween
	const Tween<float>* getExponentTween() const;

	/// @copydoc Spotlight::getExponentTween() const
	Tween<float>* getExponentTween();
	
private:
	virtual void transformed();

	Vector3 attenuation;
	Vector3 direction;
	float cutoff;
	float exponent;

	Tween<Vector3> attenuationTween;
	Tween<Vector3> directionTween;
	Tween<float> cutoffTween;
	Tween<float> exponentTween;
};

inline void Spotlight::setAttenuation(const Vector3& attenuation)
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

inline const Vector3& Spotlight::getAttenuation() const
{
	return attenuation;
}

inline const Vector3& Spotlight::getDirection() const
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

inline const Tween<Vector3>* Spotlight::getAttenuationTween() const
{
	return &attenuationTween;
}

inline Tween<Vector3>* Spotlight::getAttenuationTween()
{
	return &attenuationTween;
}

inline const Tween<Vector3>* Spotlight::getDirectionTween() const
{
	return &directionTween;
}

inline Tween<Vector3>* Spotlight::getDirectionTween()
{
	return &directionTween;
}

inline const Tween<float>* Spotlight::getCutoffTween() const
{
	return &cutoffTween;
}

inline Tween<float>* Spotlight::getCutoffTween()
{
	return &cutoffTween;
}

inline const Tween<float>* Spotlight::getExponentTween() const
{
	return &exponentTween;
}

inline Tween<float>* Spotlight::getExponentTween()
{
	return &exponentTween;
}

} // namespace Emergent

#endif // EMERGENT_GRAPHICS_LIGHT_HPP

