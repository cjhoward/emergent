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

#ifndef EMERGENT_GRAPHICS_SHADER_PARAMETER_HPP
#define EMERGENT_GRAPHICS_SHADER_PARAMETER_HPP

#include <cstdlib>
#include <string>

namespace Emergent
{

class ShaderParameterSet;

/**
 * Shader parameter
 *
 * @ingroup graphics
 */
class ShaderParameter
{
public:
	enum class Type
	{
		INT,
		FLOAT,
		VECTOR_2,
		VECTOR_3,
		VECTOR_4,
		MATRIX_3,
		MATRIX_4
	};
	
	/// Returns a pointer to the parent parameter set.
	const ShaderParameterSet* getParameterSet() const;
	
	/// Returns the index of the parameter in relation to its parent parameter set
	std::size_t getIndex() const;
	
	/// Returns the name of the parameter
	const std::string& getName() const;
	
	/// Returns the type of the parameter
	ShaderParameter::Type getType() const;
	
	/// Returns the number of elements in the parameter (for arrays)
	int getSize() const;

private:
	friend class ShaderParameterSet;
	
	/**
	 * Creates an instance of ShaderParameter.
	 *
	 * @param parameterSet Parent parameter set
	 * @param index Index of the parater, in relation to the parent parameter set
	 * @param name Name of the paramter
	 * @param type Type of the parameter
	 * @param size Number of elements in the parameter (for arrays)
	 */
	ShaderParameter(ShaderParameterSet* parameterSet, std::size_t index, const std::string& name, Type type, int size);
	
	ShaderParameterSet* parameterSet;
	std::size_t index;
	std::string name;
	Type type;
	int size;
};

inline const ShaderParameterSet* ShaderParameter::getParameterSet() const
{
	return parameterSet;
}

inline std::size_t ShaderParameter::getIndex() const
{
	return index;
}

inline const std::string& ShaderParameter::getName() const
{
	return name;
}

inline ShaderParameter::Type ShaderParameter::getType() const
{
	return type;
}

inline int ShaderParameter::getSize() const
{
	return size;
}

} // namespace Emergent

#endif // EMERGENT_GRAPHICS_SHADER_PARAMETER_HPP
