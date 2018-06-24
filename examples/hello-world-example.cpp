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
#include <sstream>

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

float wrapInterpolate(float x, float y, float a)
{
	return x * (1.0f - a) + y * a;
}

void HelloWorldExample::setup()
{
	setTitle("Hello, World!");
	setUpdateRate(60.0);

	hue.setState1(0.0f);

	stepInterpolator.addVariable(&hue);

	lastFrameDuration = 0.0;

	window->setVSync(false);

	TestEvent event1, event2, event3;
	event1.id = 1;
	event2.id = 2;
	event3.id = 3;


	eventDispatcher.subscribe<TestEvent>(this);
	eventDispatcher.schedule(event1, 1.0);
	eventDispatcher.schedule(event2, 10.0);
	eventDispatcher.schedule(event3, 1.0);

	clip.setInterpolationFunction(lerp<Vector4>);
	AnimationChannel<Vector4>* channel = clip.addChannel(0);
	channel->insertKeyframe(0.0f, Vector4(0.0f, 0.0f, 0.0f, 0.0f));
	channel->insertKeyframe(10.0f, Vector4(0.0f, 0.0f, 0.0f, 1.0f));


	screenAnimation.setClip(&clip);
	screenAnimation.setAnimateCallback(
		[this](std::size_t id, const Vector4& frame)
		{
			this->hue.setState1(frame.w);
		}
	);
	screenAnimation.setLoopCallback(
		[this]()
		{
			this->hue.setState0(this->hue.getState0() - 1.0f);
		}
	);
	screenAnimation.setSpeed(1.0f);
	screenAnimation.setLoop(true);
	screenAnimation.setTimeFrame(clip.getTimeFrame());

	// Add animations to animator
	animator.addAnimation(&screenAnimation);

	// Play animations
	screenAnimation.play();
}

void HelloWorldExample::input()
{
	controlProfile.update();
}

void HelloWorldExample::update(float t, float dt)
{
	eventDispatcher.update(t);

	animator.animate(dt);
}

void HelloWorldExample::render()
{
	float wrappedHue = std::fmod(hue.getSubstate(), 1.0f);
	if (wrappedHue < 0.0f)
	{
		wrappedHue += 1.0f;
	}

	Vector3 hsv = Vector3(wrappedHue, 1.0f, 1.0f);
	Vector3 rgb = hsvToRGB(hsv);

	glClearColor(rgb.x, rgb.y, rgb.z, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	window->swapBuffers();
}

void HelloWorldExample::exit()
{

}

void HelloWorldExample::handleEvent(const WindowResizedEvent& event)
{
	glViewport(0, 0, event.width, event.height);
}

void HelloWorldExample::handleEvent(const TestEvent& event)
{
	std::cout << "Event received!!! ID: " << event.id << std::endl;
}

/*
{
	AnimationClip<Vector4> clip;
	AnimationChannel<Vector4>* channel = clip.addChannel(0);
	channel->insertKeyframe(0.0f, Vector4(0.0f, 0.0f, 0.0f, 1.0f));
	channel->insertKeyframe(1.0f, Vector4(0.0f, 0.0f, 0.0f, 0.0f));
	clip.setTimeFrame(0.0f, 1.0f);
	clip.setSpeed(1.0f);
	clip.setRepeat(false);

	Animation<Vector4> fadeAnimation;
	fadeAnimation.setClip(&clip);
	fadeAnimation.setAnimateCallback(std::bind(asdjflask));
	fadeAnimation.setStartCallback(std::bind(dsfjhasdj));
	fadeAnimation.setEndCallback(std::bind(dsfjhasdj));

	Animator animator;
	animator.addAnimation(&fadeAnimation);

	fadeAnimation.play();

	while (1)
	{
		animator.animate(1.0f / 60.0f);
	}
}
*/

int main(int argc, char* argv[])
{
	try
	{
		return HelloWorldExample(argc, argv).execute();
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception caught: \"" << e.what() << "\"" << std::endl;
	}

	return EXIT_FAILURE;
}

