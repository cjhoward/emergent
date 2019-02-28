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

#include <emergent/graphics/shader-variable.hpp>
#include <emergent/graphics/shader-input.hpp>

namespace Emergent
{

ShaderVariableBase::ShaderVariableBase():
	connectedInput(nullptr)
{}

ShaderVariableBase::~ShaderVariableBase()
{}

bool ShaderVariableBase::connect(const ShaderInput* input)
{
	if (!input || (input->getDataType() != getDataType()))
	{
		return false;
	}
	
	connectedInput = input;
	
	return true;
}

void ShaderVariableBase::disconnect()
{
	connectedInput = nullptr;
}

} // namespace Emergent
