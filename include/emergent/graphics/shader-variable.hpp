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

#ifndef EMERGENT_GRAPHICS_SHADER_VARIABLE_HPP
#define EMERGENT_GRAPHICS_SHADER_VARIABLE_HPP

#include <emergent/math/types.hpp>
#include <emergent/graphics/shader-input.hpp>

namespace Emergent
{

class Texture2D;
class TextureCube;

/**
 * Enumerates the supported shader variable data types.
 *
 * @ingroup graphics
 */
enum class ShaderVariableType
{
	INT,         ///< Indiciates an integer type
	FLOAT,       ///< Indiciates a floating point type
	VECTOR_2,    ///< Indicates a 2D vector type
	VECTOR_3,    ///< Indicates a 3D vector type
	VECTOR_4,    ///< Indicates a 4D vector type
	MATRIX_3,    ///< Indicates a 3x3 matrix type
	MATRIX_4,    ///< Indicates a 4x4 matrix type
	TEXTURE_2D,  ///< Indicates a 2D texture type
	TEXTURE_CUBE ///< Indicates a cubemap texture type
};

/**
 * Abstract base class for shader variables.
 *
 * @ingroup graphics
 */
class ShaderVariableBase
{
public:
	/**
	 * Creates a shader variable base.
	 */
	ShaderVariableBase();
	
	/**
	 * Destroys a shader variable base.
	 */
	virtual ~ShaderVariableBase();
	
	/**
	 * Returns the type of data which the shader variable contains.
	 */
	virtual ShaderVariableType getDataType() const = 0;
	
	/**
	 * Connects this shader variable to a shader input.
	 *
	 * @param input Pointer to the shader input to which this variable should connect.
	 * @return `true` if the variable and shader input were successfully connected, `false` otherwise.
	 */
	bool connect(const ShaderInput* input);
	
	/**
	 * Disconnects the variable from its connected shader input (if any).
	 */
	void disconnect();
	
	/**
	 * Returns `true` if the variable is connected to a shader input, `false` otherwise.
	 */
	bool isConnected() const;
	
	/**
	 * Returns the connected shader input.
	 */
	const ShaderInput* getConnectedInput() const;
	
	/**
	 * Transmits the value of this shader variable to the connected shader input.
	 *
	 * @return `true` if the shader variable value was successfully uploadted, `false` otherwise.
	 */
	virtual bool upload() const = 0;
	
protected:
	const ShaderInput* connectedInput;
};

inline bool ShaderVariableBase::isConnected() const
{
	return (connectedInput != nullptr);
}

inline const ShaderInput* ShaderVariableBase::getConnectedInput() const
{
	return connectedInput;
}

/**
 * Contains data which can be passed to a shader via a shader input.
 *
 * @ingroup graphics
 */
template <typename T>
class ShaderVariable: public ShaderVariableBase
{
public:
	/**
	 * Creates a shader variable.
	 *
	 * @param elementCount Number of elements the array can hold. A value of `1` indicates the variable is not an array.
	 */
	explicit ShaderVariable(std::size_t elementCount);
	
	/**
	 * Creates a shader variable.
	 */
	ShaderVariable();
	
	/**
	 * Destroys a shader variable.
	 */
	virtual ~ShaderVariable();
	
	/// @copydoc ShaderVariableBase::upload() const
	virtual bool upload() const;
	
	/**
	 * Sets the value of this variable.
	 *
	 * @param value Value to set.
	 */
	void setValue(const T& value);
	
	/**
	 * Sets the value of a single element in this array variable.
	 *
	 * @param index Index of an array element.
	 * @param value Value to set.
	 */
	void setValue(std::size_t index, const T& value);
	
	/**
	 * Sets the values of a range of elements in this array variable.
	 *
	 * @param index Index of the first array element to set.
	 * @param values Pointer to an array of values to set.
	 * @param count Number of elements to set.
	 */
	void setValues(std::size_t index, const T* values, std::size_t count);
	
	/**
	 * Returns the number of elements in this array variable.
	 */
	std::size_t getElementCount() const;
	
	/**
	 * Returns the value of this variable.
	 */
	const T& getValue() const;
	
	/**
	 * Returns the value of a single element in this array variable.
	 *
	 * @param index Index of an array element.
	 * @return Value of the specified array element.
	 */
	const T& getValue(std::size_t index) const;
	
	/**
	 * Returns a pointer to the values of this array variable.
	 */
	const T* getValues() const;
	
	/// @copydoc ShaderVariableBase::getDataType() const
	virtual ShaderVariableType getDataType() const;
	
private:
	/// Shader variable value
	std::size_t elementCount;
	T* values;
};

template <typename T>
ShaderVariable<T>::ShaderVariable(std::size_t elementCount):
	elementCount(elementCount)
{
	values = new T[elementCount];
}

template <typename T>
ShaderVariable<T>::ShaderVariable():
	elementCount(1)
{
	values = new T[elementCount];
}

template <typename T>
ShaderVariable<T>::~ShaderVariable()
{
	delete[] values;
}

template <typename T>
bool ShaderVariable<T>::upload() const
{
	if (!isConnected())
	{
		return false;
	}
	
	if (elementCount > 1)
	{
		return connectedInput->upload(0, values, elementCount);
	}
	else
	{
		return connectedInput->upload(values[0]);
	}
}

template <typename T>
inline void ShaderVariable<T>::setValue(const T& value)
{
	this->values[0] = value;
}

template <typename T>
inline void ShaderVariable<T>::setValue(std::size_t index, const T& value)
{
	this->values[index] = value;
}

template <typename T>
inline void ShaderVariable<T>::setValues(std::size_t index, const T* values, std::size_t count)
{
	for (std::size_t i = 0; i < count; ++i)
	{
		this->values[index + i] = values[i];
	}
}

template <typename T>
inline std::size_t ShaderVariable<T>::getElementCount() const
{
	return elementCount;
}

template <typename T>
inline const T& ShaderVariable<T>::getValue() const
{
	return values[0];
}

template <typename T>
inline const T& ShaderVariable<T>::getValue(std::size_t index) const
{
	return values[index];
}

template <typename T>
inline const T* ShaderVariable<T>::getValues() const
{
	return values;
}

template <>
inline ShaderVariableType ShaderVariable<int>::getDataType() const
{
	return ShaderVariableType::INT;
}

template <>
inline ShaderVariableType ShaderVariable<float>::getDataType() const
{
	return ShaderVariableType::FLOAT;
}

template <>
inline ShaderVariableType ShaderVariable<Vector2>::getDataType() const
{
	return ShaderVariableType::VECTOR_2;
}

template <>
inline ShaderVariableType ShaderVariable<Vector3>::getDataType() const
{
	return ShaderVariableType::VECTOR_3;
}

template <>
inline ShaderVariableType ShaderVariable<Vector4>::getDataType() const
{
	return ShaderVariableType::VECTOR_4;
}

template <>
inline ShaderVariableType ShaderVariable<Matrix3>::getDataType() const
{
	return ShaderVariableType::MATRIX_3;
}

template <>
inline ShaderVariableType ShaderVariable<Matrix4>::getDataType() const
{
	return ShaderVariableType::MATRIX_4;
}

template <>
inline ShaderVariableType ShaderVariable<const Texture2D*>::getDataType() const
{
	return ShaderVariableType::TEXTURE_2D;
}

template <>
inline ShaderVariableType ShaderVariable<const TextureCube*>::getDataType() const
{
	return ShaderVariableType::TEXTURE_CUBE;
}

/**
 * Shader int variable.
 * @ingroup graphics
 */
typedef ShaderVariable<int> ShaderInt;

/**
 * Shader float variable.
 * @ingroup graphics
 */
typedef ShaderVariable<float> ShaderFloat;

/**
 * Shader vec2 variable.
 * @ingroup graphics
 */
typedef ShaderVariable<Vector2> ShaderVector2;

/**
 * Shader vec3 variable.
 * @ingroup graphics
 */
typedef ShaderVariable<Vector3> ShaderVector3;

/**
 * Shader vec4 variable.
 * @ingroup graphics
 */
typedef ShaderVariable<Vector4> ShaderVector4;

/**
 * Shader mat3 variable.
 * @ingroup graphics
 */
typedef ShaderVariable<Matrix3> ShaderMatrix3;

/**
 * Shader mat4 variable.
 * @ingroup graphics
 */
typedef ShaderVariable<Matrix4> ShaderMatrix4;

/**
 * Shader 2D texture variable.
 * @ingroup graphics
 */
typedef ShaderVariable<const Texture2D*> ShaderTexture2D;

/**
 * Shader cube texture variable.
 * @ingroup graphics
 */
typedef ShaderVariable<const TextureCube*> ShaderTextureCube;

} // namespace Emergent

#endif // EMERGENT_GRAPHICS_SHADER_VARIABLE_HPP
