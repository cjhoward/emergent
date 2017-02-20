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

#ifndef EMERGENT_GRAPHICS_SHADER_HPP
#define EMERGENT_GRAPHICS_SHADER_HPP

#include <emergent/graphics/gl3w.hpp>
#include <emergent/graphics/shader-parameter.hpp>
#include <emergent/math/types.hpp>
#include <cstdlib>
#include <vector>
#include <string>

namespace Emergent
{

class ShaderParameterSet;

/**
 * Shader
 *
 * @ingroup graphics
 */
class Shader
{
public:
	~Shader();
	
	void bind() const;
	
	/**
	 * Checks if the shader contains the specified parameter.
	 *
	 * @param parameter Specifies a parameter to check for existence.
	 * @return `true` if the shader contains specified parameter, `false` otherwise.
	 */
	bool hasParameter(const ShaderParameter* parameter) const;
	
	/**
	 * Sets a parameter value
	 *
	 * @param parameter Parameter
	 * @param value Parameter value
	 *
	 * @{
	 */
	void setParameter(const ShaderParameter* parameter, int value);
	void setParameter(const ShaderParameter* parameter, float value);
	void setParameter(const ShaderParameter* parameter, const Vector2& value);
	void setParameter(const ShaderParameter* parameter, const Vector3& value);
	void setParameter(const ShaderParameter* parameter, const Vector4& value);
	void setParameter(const ShaderParameter* parameter, const Matrix3& value);
	void setParameter(const ShaderParameter* parameter, const Matrix4& value);
	/**@}*/
	
	/**
	 * Sets a single element value within an array parameter
	 *
	 * @param parameter Array parameter
	 * @param index Index of the element to set.
	 * @param value Element value
	 *
	 * @{
	 */
	void setParameter(const ShaderParameter* parameter, std::size_t index, int value);
	void setParameter(const ShaderParameter* parameter, std::size_t index, float value);
	void setParameter(const ShaderParameter* parameter, std::size_t index, const Vector2& value);
	void setParameter(const ShaderParameter* parameter, std::size_t index, const Vector3& value);
	void setParameter(const ShaderParameter* parameter, std::size_t index, const Vector4& value);
	void setParameter(const ShaderParameter* parameter, std::size_t index, const Matrix3& value);
	void setParameter(const ShaderParameter* parameter, std::size_t index, const Matrix4& value);
	/**@}*/
	
	/**
	 * Sets multiple values within an array parameter
	 *
	 * @param parameter Array parameter
	 * @param index Index of the first element to set.
	 * @param values Element values
	 * @param count Number of elements to set
	 *
	 * @{
	 */
	void setParameter(const ShaderParameter* parameter, std::size_t index, const int* values, std::size_t count);
	void setParameter(const ShaderParameter* parameter, std::size_t index, const float* values, std::size_t count);
	void setParameter(const ShaderParameter* parameter, std::size_t index, const Vector2* values, std::size_t count);
	void setParameter(const ShaderParameter* parameter, std::size_t index, const Vector3* values, std::size_t count);
	void setParameter(const ShaderParameter* parameter, std::size_t index, const Vector4* values, std::size_t count);
	void setParameter(const ShaderParameter* parameter, std::size_t index, const Matrix3* values, std::size_t count);
	void setParameter(const ShaderParameter* parameter, std::size_t index, const Matrix4* values, std::size_t count);
	/**@}*/

private:
	friend class ShaderLoader;
	
	Shader();
	
	GLuint shaderProgram;
	GLuint vertexShader;
	GLuint fragmentShader;
	const ShaderParameterSet* parameterSet;
	std::vector<int> parameterLocations;
};

inline bool Shader::hasParameter(const ShaderParameter* parameter) const
{
	return (parameter->getParameterSet() == parameterSet && parameterLocations[parameter->getIndex()] != -1);
}

} // namespace Emergent

#endif // EMERGENT_GRAPHICS_SHADER_HPP
