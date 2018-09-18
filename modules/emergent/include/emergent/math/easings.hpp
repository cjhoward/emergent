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

/*
 * Easing Functions (Equations)
 *
 * Copyright (C) 2001 Robert Penner
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither the name of the author nor the names of contributors may be used to
 *   endorse or promote products derived from this software without specific
 *   prior written permission.

 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef EMERGENT_MATH_EASINGS_HPP
#define EMERGENT_MATH_EASINGS_HPP

#include <emergent/math/math.hpp>
#include <cmath>

namespace Emergent
{

template <typename T>
inline T easeLinear(const T& x, const T& y, float a)
{
	return (y - x) * a + x;
}

template <typename T>
T easeInSine(const T& x, const T& y, float a)
{
	return -(y - x) * std::cos(a * glm::half_pi<float>()) + (y - x) + x;
}

template <typename T>
T easeOutSine(const T& x, const T& y, float a)
{
	return (y - x) * std::sin(a * glm::half_pi<float>()) + x;
}

template <typename T>
T easeInOutSine(const T& x, const T& y, float a)
{
	return -(y - x) * 0.5f * (std::cos(glm::pi<float>() * a) - 1.0f) + x;
}

template <typename T>
T easeInQuad(const T& x, const T& y, float a)
{
	return (y - x) * a * a + x;
}

template <typename T>
T easeOutQuad(const T& x, const T& y, float a)
{
	return -(y - x) * a * (a - 2.0f) + x;
}

template <typename T>
T easeInOutQuad(const T& x, const T& y, float a)
{
	a *= 2.0f;
	if (a < 1.0f)
	{
		return (y - x) * 0.5f * a * a + x;
	}

	a -= 1.0f;
	return -(y - x) * 0.5f * (a * (a - 2.0f) - 1.0f) + x;
}

template <typename T>
T easeInCubic(const T& x, const T& y, float a)
{
	return (y - x) * a * a * a + x;
}

template <typename T>
T easeOutCubic(const T& x, const T& y, float a)
{
	a -= 1.0f;
	return (y - x) * (a * a * a + 1.0f) + x;
}

template <typename T>
T easeInOutCubic(const T& x, const T& y, float a)
{
	a *= 2.0f;
	if (a < 1.0f)
	{
		return (y - x) * 0.5f * a * a * a + x;
	}
	
	a -= 2.0f;
	return (y - x) * 0.5f * (a * a * a + 2.0f) + x;
}

template <typename T>
T easeInQuart(const T& x, const T& y, float a)
{
	return (y - x) * a * a * a * a + x;
}

template <typename T>
T easeOutQuart(const T& x, const T& y, float a)
{
	a -= 1.0f;
	return -(y - x) * (a * a * a * a - 1.0f) + x;
}

template <typename T>
T easeInOutQuart(const T& x, const T& y, float a)
{
	a *= 2.0f;
	if (a < 1.0f)
	{
		return (y - x) * 0.5f * a * a * a * a + x;
	}
	
	a -= 2.0f;
	return -(y - x) * 0.5f * (a * a * a * a - 2.0f) + x;
}

template <typename T>
T easeInQuint(const T& x, const T& y, float a)
{
	return (y - x) * a * a * a * a * a + x;
}

template <typename T>
T easeOutQuint(const T& x, const T& y, float a)
{
	a -= 1.0f;
	return (y - x) * (a * a * a * a * a + 1.0f) + x;
}

template <typename T>
T easeInOutQuint(const T& x, const T& y, float a)
{
	a *= 2.0f;
	if (a < 1.0f)
	{
		return (y - x) * 0.5f * a * a * a * a * a + x;
	}
	
	a -= 2.0f;
	return (y - x) * 0.5f * (a * a * a * a * a + 2.0f) + x;
}

template <typename T>
T easeInExpo(const T& x, const T& y, float a)
{
	if (a == 0.0f)
	{
		return x;
	}

	return (y - x) * std::pow(2.0f, 10.0f * (a - 1.0f)) + x;
}

template <typename T>
T easeOutExpo(const T& x, const T& y, float a)
{
	if (a == 1.0f)
	{
		return y;
	}

	return (y - x) * (-std::pow(2.0f, -10.0f * a) + 1.0f) + x;
}

template <typename T>
T easeInOutExpo(const T& x, const T& y, float a)
{
	if (a == 0.0f)
	{
		return x;
	}
	else if (a == 1.0f)
	{
		return y;
	}

	a *= 2.0f;
	if (a < 1.0f)
	{
		return (y - x) * 0.5f * std::pow(2.0f, 10.0f * (a - 1.0f)) + x;
	}

	a -= 1.0f;
	return (y - x) * 0.5f * (-std::pow(2.0f, -10.0f * a) + 2.0f) + x;
}

template <typename T>
T easeInCirc(const T& x, const T& y, float a)
{
	return -(y - x) * (std::sqrt(1.0f - a * a) - 1.0f) + x;
}

template <typename T>
T easeOutCirc(const T& x, const T& y, float a)
{
	a -= 1.0f;
	return (y - x) * std::sqrt(1.0f - a * a) + x;
}

template <typename T>
T easeInOutCirc(const T& x, const T& y, float a)
{
	a *= 2.0f;
	if (a < 1.0f)
	{
		return -(y - x) * 0.5f * (std::sqrt(1.0f - a * a) - 1.0f) + x;
	}
	
	a -= 2.0f;
	return (y - x) * 0.5f * (std::sqrt(1.0f - a * a) + 1.0f) + x;
}

template <typename T>
T easeInBack(const T& x, const T& y, float a)
{
	const float s = 1.70158f;
	return (y - x) * a * a * ((s + 1.0f) * a - s) + x;
}

template <typename T>
T easeOutBack(const T& x, const T& y, float a)
{
	const float s = 1.70158f;
	a -= 1.0f;
	return (y - x) * (a * a * ((s + 1.0f) * a + s) + 1.0f) + x;
}

template <typename T>
T easeInOutBack(const T& x, const T& y, float a)
{
	const float s = 1.70158f * 1.525f;

	a *= 2.0f;
	if (a < 1.0f)
	{
		return (y - x) * 0.5f * (a * a * ((s + 1.0f) * a - s)) + x;
	}

	a -= 2.0f;
	return (y - x) * 0.5f * (a * a * ((s + 1.0f) * a + s) + 2.0f) + x;
}

} // namespace Emergent

#endif // EMERGENT_MATH_EASINGS_HPP
