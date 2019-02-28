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

#ifndef EMERGENT_GRAPHICS_SHADER_INPUT_HPP
#define EMERGENT_GRAPHICS_SHADER_INPUT_HPP

#include <emergent/graphics/gl3w.hpp>
#include <emergent/math/types.hpp>
#include <string>

namespace Emergent
{

class Shader;
class Texture2D;
class TextureCube;
enum class ShaderVariableType;

/**
 * Port to which shader variables can connect in order to transmit values to a shader.
 *
 * @ingroup graphics 
 */
class ShaderInput
{
public:
	/**
	 * Returns the type of data which can be passed through this input.
	 */
	ShaderVariableType getDataType() const;
	
	/**
	 * Returns `true` if the input data is stored in an array.
	 */
	bool isArray() const;
	
	/**
	 * Returns the number of elements the array can contain, or `1` if the data is not stored in an array.
	 */
	std::size_t getElementCount() const;
	
	/**
	 * Uploads a value to the shader.
	 *
	 * @param value Value to upload.
	 * @return `true` if the value was uploaded successfully, `false` otherwise.
	 */
	///@{
	bool upload(const int& value) const;
	bool upload(const float& value) const;
	bool upload(const Vector2& value) const;
	bool upload(const Vector3& value) const;
	bool upload(const Vector4& value) const;
	bool upload(const Matrix3& value) const;
	bool upload(const Matrix4& value) const;
	bool upload(const Texture2D* value) const;
	bool upload(const TextureCube* value) const;
	///@}
	
	/**
	 * Uploads a single array element to the shader.
	 *
	 * @param index Index of an array element.
	 * @param values Value to upload.
	 * @return `true` if the value was uploaded successfully, `false` otherwise.
	 */
	///@{
	bool upload(std::size_t index, const int& value) const;
	bool upload(std::size_t index, const float& value) const;
	bool upload(std::size_t index, const Vector2& value) const;
	bool upload(std::size_t index, const Vector3& value) const;
	bool upload(std::size_t index, const Vector4& value) const;
	bool upload(std::size_t index, const Matrix3& value) const;
	bool upload(std::size_t index, const Matrix4& value) const;
	bool upload(std::size_t index, const Texture2D* value) const;
	bool upload(std::size_t index, const TextureCube* value) const;
	///@}
	
	/**
	 * Uploads a range of array elements to the shader.
	 *
	 * @param index Index of the first array element.
	 * @param values Pointer to an array of values.
	 * @param count Number of elements to upload.
	 * @return `true` if the value was fed successfully, `false` otherwise.
	 */
	///@{
	bool upload(std::size_t index, const int* values, std::size_t count) const;
	bool upload(std::size_t index, const float* values, std::size_t count) const;
	bool upload(std::size_t index, const Vector2* values, std::size_t count) const;
	bool upload(std::size_t index, const Vector3* values, std::size_t count) const;
	bool upload(std::size_t index, const Vector4* values, std::size_t count) const;
	bool upload(std::size_t index, const Matrix3* values, std::size_t count) const;
	bool upload(std::size_t index, const Matrix4* values, std::size_t count) const;
	bool upload(std::size_t index, const Texture2D** values, std::size_t count) const;
	bool upload(std::size_t index, const TextureCube** values, std::size_t count) const;
	///@}
	
private:
	friend class Shader;
	template <typename T>
	friend class ShaderVariable;
	
	/**
	 * Creates a shader input.
	 *
	 * @param shader Shader with which this input is associated.
	 * @param uniformLocation Location of the shader uniform with which this shader input is associated.
	 * @param name Name of the input.
	 * @param dataType Type of data which can be passed through this input.
	 * @param elementCount Number of elements which the array can contain, or `0` if input data is not stored in an array.
	 * @param textureUnit Texture unit to which texture shader variables can be bound, or `-1` if the data type is not a texture type.
	 */
	ShaderInput(Shader* shader, std::size_t inputIndex, GLint uniformLocation, const std::string& name, ShaderVariableType dataType, std::size_t elementCount, int textureUnit);
	
	/**
	 * Destroys a shader input.
	 */
	~ShaderInput();
	
	Shader* shader;
	std::size_t inputIndex;
	GLint uniformLocation;
	std::string name;
	ShaderVariableType dataType;
	std::size_t elementCount;
	int textureUnit;
};

inline ShaderVariableType ShaderInput::getDataType() const
{
	return dataType;
}

inline bool ShaderInput::isArray() const
{
	return (elementCount > 1);
}

inline std::size_t ShaderInput::getElementCount() const
{
	return elementCount;
}

} // namespace Emergent

#endif // EMERGENT_GRAPHICS_SHADER_INPUT_HPP
