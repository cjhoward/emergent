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

#include <emergent/graphics/shader-input.hpp>
#include <emergent/graphics/texture-2d.hpp>
#include <emergent/graphics/texture-cube.hpp>

namespace Emergent
{

ShaderInput::ShaderInput(Shader* shader, std::size_t inputIndex, GLint uniformLocation, const std::string& name, ShaderVariableType dataType, std::size_t elementCount, int textureUnit):
	shader(shader),
	inputIndex(inputIndex),
	uniformLocation(uniformLocation),
	name(name),
	dataType(dataType),
	elementCount(elementCount),
	textureUnit(textureUnit)
{}

ShaderInput::~ShaderInput()
{}

bool ShaderInput::upload(const int& value) const
{
	if (uniformLocation == -1)
		return false;
	
	glUniform1i(uniformLocation, value);
	return true;
}

bool ShaderInput::upload(const float& value) const
{
	if (uniformLocation == -1)
		return false;
	
	glUniform1f(uniformLocation, value);
	return true;
}

bool ShaderInput::upload(const Vector2& value) const
{
	if (uniformLocation == -1)
		return false;
	
	glUniform2fv(uniformLocation, 1, glm::value_ptr(value));
	return true;
}

bool ShaderInput::upload(const Vector3& value) const
{
	if (uniformLocation == -1)
		return false;
	
	glUniform3fv(uniformLocation, 1, glm::value_ptr(value));
	return true;
}

bool ShaderInput::upload(const Vector4& value) const
{
	if (uniformLocation == -1)
		return false;
	
	glUniform4fv(uniformLocation, 1, glm::value_ptr(value));
	return true;
}

bool ShaderInput::upload(const Matrix3& value) const
{
	if (uniformLocation == -1)
		return false;
	
	glUniformMatrix3fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(value));
	return true;
}

bool ShaderInput::upload(const Matrix4& value) const
{
	if (uniformLocation == -1)
		return false;
	
	glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(value));
	return true;
}

bool ShaderInput::upload(const Texture2D* value) const
{
	if (uniformLocation == -1)
		return false;
	
	// Bind texture to a texture unit reserved by this shader input
	glActiveTexture(GL_TEXTURE0 + textureUnit);
	glBindTexture(GL_TEXTURE_2D, value->getTextureID());
	
	// Upload texture unit index to shader
	glUniform1i(uniformLocation, textureUnit);
	
	return true;
}

bool ShaderInput::upload(const TextureCube* value) const
{
	if (uniformLocation == -1)
		return false;
	
	// Bind texture to a texture unit reserved by this shader input
	glActiveTexture(GL_TEXTURE0 + textureUnit);
	glBindTexture(GL_TEXTURE_CUBE_MAP, value->getTextureID());
	
	// Upload texture unit index to shader
	glUniform1i(uniformLocation, textureUnit);
	
	return true;
}

bool ShaderInput::upload(std::size_t index, const int& value) const
{
	if (uniformLocation == -1)
		return false;
	
	glUniform1i(uniformLocation + index, value);
	return true;
}

bool ShaderInput::upload(std::size_t index, const float& value) const
{
	if (uniformLocation == -1)
		return false;
	
	glUniform1f(uniformLocation + index, value);
	return true;
}

bool ShaderInput::upload(std::size_t index, const Vector2& value) const
{
	if (uniformLocation == -1)
		return false;
	
	glUniform2fv(uniformLocation + index, 1, glm::value_ptr(value));
	return true;
}

bool ShaderInput::upload(std::size_t index, const Vector3& value) const
{
	if (uniformLocation == -1)
		return false;
	
	glUniform3fv(uniformLocation + index, 1, glm::value_ptr(value));
	return true;
}

bool ShaderInput::upload(std::size_t index, const Vector4& value) const
{
	if (uniformLocation == -1)
		return false;
	
	glUniform4fv(uniformLocation + index, 1, glm::value_ptr(value));
	return true;
}

bool ShaderInput::upload(std::size_t index, const Matrix3& value) const
{
	if (uniformLocation == -1)
		return false;
	
	glUniformMatrix3fv(uniformLocation + index * 3, 1, GL_FALSE, glm::value_ptr(value));
	return true;
}

bool ShaderInput::upload(std::size_t index, const Matrix4& value) const
{
	if (uniformLocation == -1)
		return false;
	
	glUniformMatrix4fv(uniformLocation + index * 4, 1, GL_FALSE, glm::value_ptr(value));
	return true;
}

bool ShaderInput::upload(std::size_t index, const Texture2D* value) const
{
	if (uniformLocation == -1)
		return false;
	
	// Bind texture to a texture unit reserved by this shader input
	glActiveTexture(GL_TEXTURE0 + textureUnit + index);
	glBindTexture(GL_TEXTURE_2D, value->getTextureID());
	
	// Upload texture unit index to shader
	glUniform1i(uniformLocation + index, textureUnit + index);
	
	return true;
}

bool ShaderInput::upload(std::size_t index, const TextureCube* value) const
{
	if (uniformLocation == -1)
		return false;
	
	// Bind texture to a texture unit reserved by this shader input
	glActiveTexture(GL_TEXTURE0 + textureUnit + index);
	glBindTexture(GL_TEXTURE_CUBE_MAP, value->getTextureID());
	
	// Upload texture unit index to shader
	glUniform1i(uniformLocation + index, textureUnit + index);
	
	return true;
}

bool ShaderInput::upload(std::size_t index, const int* values, std::size_t count) const
{
	if (uniformLocation == -1)
		return false;
	
	glUniform1iv(uniformLocation + index, static_cast<GLsizei>(count), &values[0]);
	return true;
}

bool ShaderInput::upload(std::size_t index, const float* values, std::size_t count) const
{
	if (uniformLocation == -1)
		return false;
	
	glUniform1fv(uniformLocation + index, static_cast<GLsizei>(count), &values[0]);
	return true;
}

bool ShaderInput::upload(std::size_t index, const Vector2* values, std::size_t count) const
{
	if (uniformLocation == -1)
		return false;
	
	glUniform2fv(uniformLocation + index, static_cast<GLsizei>(count), glm::value_ptr(values[0]));
	return true;
}

bool ShaderInput::upload(std::size_t index, const Vector3* values, std::size_t count) const
{
	if (uniformLocation == -1)
		return false;
	
	glUniform3fv(uniformLocation + index, static_cast<GLsizei>(count), glm::value_ptr(values[0]));
	return true;
}

bool ShaderInput::upload(std::size_t index, const Vector4* values, std::size_t count) const
{
	if (uniformLocation == -1)
		return false;
	
	glUniform4fv(uniformLocation + index, static_cast<GLsizei>(count), glm::value_ptr(values[0]));
	return true;
}

bool ShaderInput::upload(std::size_t index, const Matrix3* values, std::size_t count) const
{
	if (uniformLocation == -1)
		return false;
	
	glUniformMatrix3fv(uniformLocation + index * 3, static_cast<GLsizei>(count), GL_FALSE, glm::value_ptr(values[0]));
	return true;
}

bool ShaderInput::upload(std::size_t index, const Matrix4* values, std::size_t count) const
{
	if (uniformLocation == -1)
		return false;
	
	glUniformMatrix4fv(uniformLocation + index * 4, static_cast<GLsizei>(count), GL_FALSE, glm::value_ptr(values[0]));
	return true;
}

bool ShaderInput::upload(std::size_t index, const Texture2D** values, std::size_t count) const
{
	if (uniformLocation == -1)
		return false;
	
	for (std::size_t i = 0; i < count; ++i)
	{
		// Bind texture to a texture unit reserved by this shader input
		glActiveTexture(GL_TEXTURE0 + textureUnit + index + i);
		glBindTexture(GL_TEXTURE_2D, values[i]->getTextureID());
		
		// Upload texture unit index to shader
		glUniform1i(uniformLocation + index + i, textureUnit + index + i);
	}
	
	return true;
}

bool ShaderInput::upload(std::size_t index, const TextureCube** values, std::size_t count) const
{
	if (uniformLocation == -1)
		return false;
	
	for (std::size_t i = 0; i < count; ++i)
	{
		// Bind texture to a texture unit reserved by this shader input
		glActiveTexture(GL_TEXTURE0 + textureUnit + index + i);
		glBindTexture(GL_TEXTURE_CUBE_MAP, values[i]->getTextureID());
		
		// Upload texture unit index to shader
		glUniform1i(uniformLocation + index + i, textureUnit + index + i);
	}
	
	return true;
}

} // namespace Emergent
