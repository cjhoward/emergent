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

#ifndef EMERGENT_GRAPHICS_MATERIAL_HPP
#define EMERGENT_GRAPHICS_MATERIAL_HPP

#include <emergent/graphics/shader-variable.hpp>
#include <emergent/graphics/shader.hpp>
#include <cstdint>
#include <map>
#include <string>
#include <vector>

namespace Emergent
{

/**
 * Materials are associated with a single shader and contain a set of shader variables.
 *
 * @ingroup graphics
 */
class Material
{
public:
	/**
	 * Creates a material.
	 *
	 * @param shader Shader with which to associate this material.
	 */
	explicit Material(Shader* shader);
	
	/**
	 * Creates a material.
	 */
	Material();
	
	/**
	 * Destroys a material.
	 */
	~Material();
	
	/**
	 * Associates this material with a shader.
	 *
	 * @param shader Shader with which to associate this material.
	 */
	void setShader(Shader* shader);
	
	/**
	 * Adds a shader variable to the material.
	 *
	 * @param inputName Name of a shader input to which this variable should be connected.
	 * @param elementCount Number of elements the array can hold.
	 * @return Newly created shader variable, or `nullptr` if the material already has a variable associated with the specified input name.
	 */
	template <typename T>
	ShaderVariable<T>* addVariable(const std::string& inputName, std::size_t elementCount);
	
	/**
	 * Adds a shader variable to the material.
	 *
	 * @param inputName Name of a shader input to which this variable should be connected.
	 * @return Newly created shader variable, or `nullptr` if the material already has a variable associated with the specified input name.
	 */
	template <typename T>
	ShaderVariable<T>* addVariable(const std::string& inputName);
	
	/**
	 * Removes and deletes all variables from the material.
	 */
	void removeVariables();
	
	/**
	 * Sets the material flags.
	 *
	 * @param flags Material flags
	 */
	void setFlags(std::uint32_t flags);
	
	/**
	 * Returns the shader associated with this material.
	 */
	const Shader* getShader() const;
	
	/// @copydoc Material::getShader() const
	Shader* getShader();
	
	/**
	 * Returns the number of shader variables in the material.
	 */
	std::size_t getVariableCount() const;
	
	/**
	 * Returns the shader variable at the specified index.
	 *
	 * @param index Index of a shader variable.
	 * @return Pointer to the shader variable at the specified index.
	 */
	const ShaderVariableBase* getVariable(std::size_t index) const;
	
	/// @copydoc Material::getVariable(std::size_t) const
	ShaderVariableBase* getVariable(std::size_t index);
	
	/**
	 * Returns the shader variable which is associated with the specified shader input name.
	 *
	 * @param inputName Name of a shader input.
	 * @return Pointer to the shader variable associated with the specified input name, or `nullptr` if a corresponding shader variable was not found.
	 */
	const ShaderVariableBase* getVariable(const std::string& inputName) const;
	
	/// @copydoc Material::getVariable(std::size_t) const
	ShaderVariableBase* getVariable(const std::string& inputName);
	
	/**
	 * Returns the material flags. Flags may be interpreted by a render pass in order to sort render operations or perform other functions.
	 */
	std::uint64_t getFlags() const;
	
	/**
	 * Calls the `ShaderVariableBase::upload() const` function of each shader variable in the material.
	 *
	 * @return `true` if all variables were successfully uploaded, `false` otherwise.
	 */
	bool upload() const;
	
private:
	friend class Shader;
	
	/**
	 * Attempts to reconnect all shader variables to shader inputs.
	 */
	void reconnectVariables();
	
	Shader* shader;
	std::vector<ShaderVariableBase*> variables;
	std::map<std::string, std::size_t> variableMap;
	std::uint64_t flags;
};

template <typename T>
ShaderVariable<T>* Material::addVariable(const std::string& inputName, std::size_t elementCount)
{
	auto it = variableMap.find(inputName);
	if (it != variableMap.end())
	{
		// Another variable is already associated with the specified shader input name
		return nullptr;
	}
	
	// Allocate new shader variable
	ShaderVariable<T>* variable = new ShaderVariable<T>(elementCount);
	
	// Add variable to the shader variable vector and map
	variableMap[inputName] = variables.size();
	variables.push_back(variable);
	
	// Attempt to connect the variable
	if (shader != nullptr)
	{
		variable->connect(shader->getInput(inputName));
	}
	
	return variable;
}

template <typename T>
ShaderVariable<T>* Material::addVariable(const std::string& inputName)
{
	return addVariable<T>(inputName, 1);
}

inline void Material::setFlags(std::uint32_t flags)
{
	this->flags = flags;
}

inline const Shader* Material::getShader() const
{
	return shader;
}
	
inline Shader* Material::getShader()
{
	return shader;
}

inline std::size_t Material::getVariableCount() const
{
	return variables.size();
}

inline const ShaderVariableBase* Material::getVariable(std::size_t index) const
{
	return variables[index];
}

inline ShaderVariableBase* Material::getVariable(std::size_t index)
{
	return variables[index];
}

inline std::uint64_t Material::getFlags() const
{
	return flags;
}

} // namespace Emergent

#endif // EMERGENT_GRAPHICS_MATERIAL_HPP
