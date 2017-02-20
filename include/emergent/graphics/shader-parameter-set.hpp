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

#ifndef EMERGENT_GRAPHICS_SHADER_PARAMETER_SET_HPP
#define EMERGENT_GRAPHICS_SHADER_PARAMETER_SET_HPP

#include <emergent/graphics/shader-parameter.hpp>

#include <cstdlib>
#include <string>
#include <vector>

namespace Emergent
{

/**
 * A set of shader parameters which is used when loading one or more shaders.
 *
 * @ingroup graphics
 */
class ShaderParameterSet
{
public:
	/**
	 * Creates an instance of ShaderParameterSet.
	 */
	ShaderParameterSet();
	
	/**
	 * Destroys an instance of ShaderParameterSet.
	 */
	~ShaderParameterSet();
	
	/**
	 * Adds a parameter to the parameter set. Must be called **before** loading any shaders with this parameter set.
	 *
	 * @param name Name of the parameter
	 * @param type Type of the parameter
	 * @param size Number of elements in the parameter (if it's an array)
	 *
	 * @return Pointer to the added parameter.
	 */
	const ShaderParameter* addParameter(const std::string& name, ShaderParameter::Type type, int size);
	
	/**
	 * Removes all parameters from the set.
	 */
	void removeParameters();
	
	/**
	 * Returns the number of parameters in the set.
	 */
	std::size_t getParameterCount() const;
	
	/**
	 * Returns the parameter at the specified index.
	 *
	 * @param index Index of a shader parameter.
	 */
	const ShaderParameter* getParameter(std::size_t index) const;

private:
	std::vector<ShaderParameter*> parameters;
};

inline std::size_t ShaderParameterSet::getParameterCount() const
{
	return parameters.size();
}

inline const ShaderParameter* ShaderParameterSet::getParameter(std::size_t index) const
{
	return parameters[index];
}

} // namespace Emergent

#endif // EMERGENT_GRAPHICS_SHADER_PARAMETER_SET_HPP
