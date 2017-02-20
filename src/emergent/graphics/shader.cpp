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

#include <emergent/graphics/shader.hpp>
#include <emergent/graphics/gl3w.hpp>

namespace Emergent
{

Shader::Shader()
{}

Shader::~Shader()
{
	glDetachShader(shaderProgram, vertexShader);
	glDetachShader(shaderProgram, fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteProgram(shaderProgram);
}

void Shader::bind() const
{
	glUseProgram(shaderProgram);
}

void Shader::setParameter(const ShaderParameter* parameter, int value)
{
	glUniform1i(parameterLocations[parameter->getIndex()], value);
}

void Shader::setParameter(const ShaderParameter* parameter, float value)
{
	glUniform1f(parameterLocations[parameter->getIndex()], value);
}

void Shader::setParameter(const ShaderParameter* parameter, const Vector2& value)
{
	glUniform2fv(parameterLocations[parameter->getIndex()], 1, glm::value_ptr(value));
}

void Shader::setParameter(const ShaderParameter* parameter, const Vector3& value)
{
	glUniform3fv(parameterLocations[parameter->getIndex()], 1, glm::value_ptr(value));
}

void Shader::setParameter(const ShaderParameter* parameter, const Vector4& value)
{
	glUniform4fv(parameterLocations[parameter->getIndex()], 1, glm::value_ptr(value));
}

void Shader::setParameter(const ShaderParameter* parameter, const Matrix3& value)
{
	glUniformMatrix3fv(parameterLocations[parameter->getIndex()], 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setParameter(const ShaderParameter* parameter, const Matrix4& value)
{
	glUniformMatrix4fv(parameterLocations[parameter->getIndex()], 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setParameter(const ShaderParameter* parameter, std::size_t index, int value)
{
	glUniform1i(parameterLocations[parameter->getIndex()] + index, value);
}

void Shader::setParameter(const ShaderParameter* parameter, std::size_t index, float value)
{
	glUniform1f(parameterLocations[parameter->getIndex()] + index, value);
}

void Shader::setParameter(const ShaderParameter* parameter, std::size_t index, const Vector2& value)
{
	glUniform2fv(parameterLocations[parameter->getIndex()] + index, 1, glm::value_ptr(value));
}

void Shader::setParameter(const ShaderParameter* parameter, std::size_t index, const Vector3& value)
{
	glUniform3fv(parameterLocations[parameter->getIndex()] + index, 1, glm::value_ptr(value));
}

void Shader::setParameter(const ShaderParameter* parameter, std::size_t index, const Vector4& value)
{
	glUniform4fv(parameterLocations[parameter->getIndex()] + index, 1, glm::value_ptr(value));
}

void Shader::setParameter(const ShaderParameter* parameter, std::size_t index, const Matrix3& value)
{
	glUniformMatrix3fv(parameterLocations[parameter->getIndex()] + index * 3, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setParameter(const ShaderParameter* parameter, std::size_t index, const Matrix4& value)
{
	glUniformMatrix4fv(parameterLocations[parameter->getIndex()] + index * 4, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setParameter(const ShaderParameter* parameter, std::size_t index, const int* values, std::size_t count)
{
	glUniform1iv(parameterLocations[parameter->getIndex()] + index, static_cast<GLsizei>(count), values);
}

void Shader::setParameter(const ShaderParameter* parameter, std::size_t index, const float* values, std::size_t count)
{
	glUniform1fv(parameterLocations[parameter->getIndex()] + index, static_cast<GLsizei>(count), values);
}

void Shader::setParameter(const ShaderParameter* parameter, std::size_t index, const Vector2* values, std::size_t count)
{
	glUniform2fv(parameterLocations[parameter->getIndex()] + index, static_cast<GLsizei>(count), glm::value_ptr(values[0]));
}

void Shader::setParameter(const ShaderParameter* parameter, std::size_t index, const Vector3* values, std::size_t count)
{
	glUniform3fv(parameterLocations[parameter->getIndex()] + index, static_cast<GLsizei>(count), glm::value_ptr(values[0]));
}

void Shader::setParameter(const ShaderParameter* parameter, std::size_t index, const Vector4* values, std::size_t count)
{
	glUniform4fv(parameterLocations[parameter->getIndex()] + index, static_cast<GLsizei>(count), glm::value_ptr(values[0]));
}

void Shader::setParameter(const ShaderParameter* parameter, std::size_t index, const Matrix3* values, std::size_t count)
{
	glUniformMatrix3fv(parameterLocations[parameter->getIndex()] + index * 3, static_cast<GLsizei>(count), GL_FALSE, glm::value_ptr(values[0]));
}

void Shader::setParameter(const ShaderParameter* parameter, std::size_t index, const Matrix4* values, std::size_t count)
{
	glUniformMatrix4fv(parameterLocations[parameter->getIndex()] + index * 4, static_cast<GLsizei>(count), GL_FALSE, glm::value_ptr(values[0]));
}

} // namespace Emergent
