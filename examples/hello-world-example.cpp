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

#include "hello-world-example.hpp"

HelloWorldExample::HelloWorldExample(int argc, char* argv[]):
	ExampleApplication(argc, argv)
{}

HelloWorldExample::~HelloWorldExample()
{}

Vector3 hsvToRGB(Vector3 hsv)
{
	Vector3 rgb;

	hsv.x = std::max<float>(0.0f, std::min<float>(1.0f, hsv.x));
	hsv.y = std::max<float>(0.0f, std::min<float>(1.0f, hsv.y));
	hsv.z = std::max<float>(0.0f, std::min<float>(1.0f, hsv.z));

	// Achromatic
	if (!hsv.z)
	{
		rgb.x = rgb.y = rgb.z = hsv.z;
		return rgb;
	}

	int sector = static_cast<int>(hsv.x * 6.0f);
	float f = (hsv.x * 6.0f) - sector;
	float p = hsv.z * (1.0f - hsv.y);
	float q = hsv.z * (1.0f - hsv.y * f);
	float t = hsv.z * (1.0f - hsv.y * (1.0f - f));

	switch (sector)
	{
		case 0:
		case 6:
			rgb.x = hsv.z;
			rgb.y = t;
			rgb.z = p;
			break;

		case 1:
			rgb.x = q;
			rgb.y = hsv.z;
			rgb.z = p;
			break;

		case 2:
			rgb.x = p;
			rgb.y = hsv.z;
			rgb.z = t;
			break;

		case 3:
			rgb.x = p;
			rgb.y = q;
			rgb.z = hsv.z;
			break;

		case 4:
			rgb.x = t;
			rgb.y = p;
			rgb.z = hsv.z;
			break;

		default:
			rgb.x = hsv.z;
			rgb.y = p;
			rgb.z = q;
			break;
	}

	return rgb;
}

void HelloWorldExample::setup()
{
	setTitle("Hello, World!");
	hue = 0.0f;
}

void HelloWorldExample::update(float dt)
{
	hue += 0.25f * dt;
	while (hue >= 1.0f) hue -= 1.0f;
	hsv = Vector3(hue, 1.0f, 1.0f);
	rgb = hsvToRGB(hsv);
}

void HelloWorldExample::draw()
{
	glClearColor(rgb.x, rgb.y, rgb.z, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void HelloWorldExample::windowResized(int width, int height)
{
	glViewport(0, 0, width, height);
}

int main(int argc, char* argv[])
{
	return HelloWorldExample(argc, argv).execute();
}

