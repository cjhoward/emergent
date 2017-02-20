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

#ifndef EMERGENT_GRAPHICS_SHADER_LOADER_HPP
#define EMERGENT_GRAPHICS_SHADER_LOADER_HPP

#include <emergent/graphics/gl3w.hpp>
#include <cstdlib>
#include <vector>
#include <string>

namespace Emergent
{

class Shader;
class ShaderParameterSet;

/**
 * Loads shaders
 *
 * @ingroup graphics
 */
class ShaderLoader
{
public:
	// Defines a preprocessor macro
	void define(const std::string& name);
	void define(const std::string& name, int value);
	void define(const std::string& name, float value);
	void define(const std::string& name, const std::string& value);
	
	// Removes all definitions
	void undefine();
	
	/**
	 * Loads a shader program from a single file. The file will be loaded twice, the first with the macro definition _VERTEX_SHADER defined in order to create a vertex shader, and the second with _FRAGMENT_SHADER defined in order to create a fragment shader. Both macro definitions are inserted immediately following the `#version` directive.
	 *
	 * @param filename Name of the shader program file.
	 * @param parameterSet Set of parameters with which to load the shader program.
	 */
	Shader* load(const std::string& filename, const ShaderParameterSet* parameterSet) const;

private:
	static bool checkShaderCompileStatus(GLuint shader, std::string* log);
	static bool checkProgramLinkStatus(GLuint program, std::string* log);
	
	bool loadShader(const std::string& filename, GLuint* shader, GLenum shaderType) const;
	bool loadSource(const std::string& filename, std::string* source) const;
	bool readSource(const std::string& filename, std::vector<std::string>* sourceLines) const;
	bool preprocess(const std::string& filename, std::vector<std::string>* sourceLines) const;
	
	mutable std::vector<std::string> definitions;
};

} // namespace Emergent

#endif // EMERGENT_GRAPHICS_SHADER_LOADER_HPP
