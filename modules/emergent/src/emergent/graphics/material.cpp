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

#include <emergent/graphics/material.hpp>

namespace Emergent
{

Material::Material(Shader* shader):
	shader(shader),
	flags(0)
{}

Material::Material():
	shader(nullptr),
	flags(0)
{}

Material::~Material()
{
	// Unlink material from shader
	if (this->shader != nullptr)
	{
		this->shader->unlinkMaterial(this);
	}
	
	removeVariables();
}

void Material::setShader(Shader* shader)
{
	// Unlink material from old shader
	if (this->shader != nullptr)
	{
		this->shader->unlinkMaterial(this);
	}
	
	// Link material to new shader
	this->shader = shader;
	if (this->shader != nullptr)
	{
		this->shader->linkMaterial(this);
	}
	
	reconnectVariables();
}

void Material::removeVariables()
{
	for (ShaderVariableBase* variable: variables)
	{
		delete variable;
	}
	
	variables.clear();
	variableMap.clear();
}

const ShaderVariableBase* Material::getVariable(const std::string& inputName) const
{
	auto it = variableMap.find(inputName);
	if (it == variableMap.end())
	{
		return nullptr;
	}
	
	return variables[it->second];
}

ShaderVariableBase* Material::getVariable(const std::string& inputName)
{
	auto it = variableMap.find(inputName);
	if (it == variableMap.end())
	{
		return nullptr;
	}
	
	return variables[it->second];
}

void Material::reconnectVariables()
{
	for (auto it = variableMap.begin(); it != variableMap.end(); ++it)
	{
		ShaderVariableBase* variable = variables[it->second];
		
		// Disconnect variable
		variable->disconnect();
		
		// If material has a valid shader, attempt to connect the variable
		if (shader != nullptr)
		{
			variable->connect(shader->getInput(it->first));
		}
	}
}

bool Material::upload() const
{
	int transmissions = 0;
	
	for (const ShaderVariableBase* variable: variables)
	{
		if (variable->upload())
		{
			++transmissions;
		}
	}

	return (transmissions == variables.size());
}

Material* Material::clone() const
{
	Material* material = new Material();
	material->setShader(shader); 
	for (std::size_t i = 0; i < variables.size(); ++i)
	{
		material->variables.push_back(variables[i]->clone());
	}
	material->variableMap = variableMap;
	material->flags = flags;
	return material;
}

} // namespace Emergent
