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

#include <emergent/graphics/light.hpp>
#include <emergent/math/interpolation.hpp>

namespace Emergent
{

PunctualLight::PunctualLight():
	color(1.0f),
	intensity(1.0f),
	scaledColor(1.0f),
	colorTween(&color, lerp<Vector3>),
	intensityTween(&intensity, lerp<float>)
{
	registerTween(&colorTween);
	registerTween(&intensityTween);
}

PunctualLight::~PunctualLight()
{}

Light::Light()
{}

Light::~Light()
{}

PointLight::PointLight():
	attenuation(1.0f, 0.0f, 0.0f),
	attenuationTween(&attenuation, lerp<Vector3>)
{
	registerTween(&attenuationTween);
}

PointLight::~PointLight()
{}

DirectionalLight::DirectionalLight():
	direction(0, 0, -1),
	directionTween(&direction, lerp<Vector3>)
{
	registerTween(&directionTween);
}

DirectionalLight::~DirectionalLight()
{}

void DirectionalLight::setDirection(const Vector3& direction)
{
	setRotation(glm::rotation(Vector3(0.0f, 0.0f, -1.0f), direction));
}

void DirectionalLight::transformed()
{
	direction = glm::normalize(getRotation() * Vector3(0.0f, 0.0f, -1.0f));
}

Spotlight::Spotlight():
	attenuation(1, 0, 0),
	direction(0, 0, -1),
	cutoff(glm::pi<float>()),
	exponent(0.0f),
	attenuationTween(&attenuation, lerp<Vector3>),
	directionTween(&direction, lerp<Vector3>),
	cutoffTween(&cutoff, lerp<float>),
	exponentTween(&exponent, lerp<float>)
{
	registerTween(&attenuationTween);
	registerTween(&directionTween);
	registerTween(&cutoffTween);
	registerTween(&exponentTween);
}

Spotlight::~Spotlight()
{}

void Spotlight::setDirection(const Vector3& direction)
{
	setRotation(glm::rotation(Vector3(0.0f, 0.0f, -1.0f), direction));
}

void Spotlight::transformed()
{
	direction = glm::normalize(getRotation() * Vector3(0.0f, 0.0f, -1.0f));
}

} // namespace Emergent
