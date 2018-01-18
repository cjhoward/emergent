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

#ifndef EMERGENT_GRAPHICS_SHADER_HPP
#define EMERGENT_GRAPHICS_SHADER_HPP

#include <emergent/graphics/gl3w.hpp>
#include <emergent/math/types.hpp>
#include <cstdint>
#include <cstdlib>
#include <list>
#include <map>
#include <string>
#include <vector>

namespace Emergent
{

class ShaderInput;

/**
 * Single permutation of a shader program.
 *
 * @ingroup graphics
 */
class ShaderPermutation
{
public:
	/**
	 * Creates a shader permutation.
	 *
	 * @param permutationValue Unique permutation value.
	 * @param shaderProgram Precompiled shader program.
	 * @param vertexShader Precompiled vertex shader.
	 * @param geometryShader Precompiled geometry shader.
	 * @param fragmentShader Precompiled fragment shader.
	 */
	ShaderPermutation(std::uint32_t permutationValue, GLuint shaderProgram, GLuint vertexShader, GLuint geometryShader, GLuint fragmentShader);
	
	/**
	 * Destroys a shader permutation and deletes associated shaders and shader program.
	 */
	~ShaderPermutation();
	
	std::uint32_t permutationValue;
	GLuint shaderProgram;
	GLuint vertexShader;
	GLuint geometryShader;
	GLuint fragmentShader;
	std::vector<GLint> uniformLocations;
};

/**
 * The shader class is a collection of permutations of a shader program. A shader provides access to shader uniforms via shader inputs, which route data to uniform locations according to the active permutation.
 *
 * @ingroup graphics
 */
class Shader
{
public:
	/**
	 * Creates a shader.
	 */
	Shader();
	
	/**
	 * Destroys a shader.
	 */
	~Shader();
	
	/**
	 * Loads the shader source from a file. No shaders are generated during this process.
	 *
	 * @param filename Path to a shader source file.
	 */
	bool loadSource(const std::string& filename);
	
	/**
	 * Generates a shader permutation. The specified 32-bit permutation value is injected into the shader source before compilation as the preprocessor definition `__PERMUTATION__`. This definition can be parsed for bit flags and other information in order to selectively enable features at compile-time.
	 *
	 * Preprocessor directives:
	 * * `#pragma include "file.inc"` will replace the current line with the contents of the file `file.inc`
	 * * `#pragma vertex` causes a vertex shader to be generated with the preprocessor definition `__VERTEX__` defined.
	 * * `#pragma geometry` causes a geometry shader to be generated with the preprocessor definition `__GEOMETRY__` defined.
	 * * `#pragma fragment` causes a fragment shader to be generated with the preprocessor definition `__FRAGMENT__` defined.
	 *
	 * @param permutation Permutation value which will be injected into the shader source as `__PERMUTATION__` before compilation.
	 * @return `true` if the permutation was generated successfully, `false` otherwise.
	 */
	bool generatePermutation(std::uint32_t permutation);
	
	/**
	 * Deletes all generated shader permutations and shader inputs.
	 */
	void deleteAllPermutations();
	
	/**
	 * Binds a permutation's shader program and routes shader inputs to the permutation's uniform locations.
	 *
	 * @param permutation Value of the permutation to be activated.
	 * @return `true` if the permutation was bound successfully, `false` otherwise.
	 */
	bool activate(std::uint32_t permutation);
	
	/**
	 * Checks if a shader permutation with the specified permutation value has been generated.
	 *
	 * @param permutation Permutation value
	 * @return `true` if a shader permutation with the specified value has been generated, `false` otherwise.
	 */
	bool hasPermutation(std::uint32_t permutation) const;
	
	/**
	 * Returns the number of shader inputs.
	 */
	std::size_t getInputCount() const;
	
	/**
	 * Returns the shader input at the specified index.
	 *
	 * @param index Index of a shader input.
	 * @return Shader input at the specified index.
	 */
	const ShaderInput* getInput(std::size_t index) const;
	
	/**
	 * Returns the shader input with the specified name.
	 *
	 * @param name Name of a shader input.
	 * @return Shader input with the specified name, or `nullptr` if no matching input was found.
	 */
	const ShaderInput* getInput(const std::string& name) const;
	
private:
	friend class Material;
	
	/**
	 * Reads the contents of a file into a vector of lines.
	 *
	 * @param filename Path to a file
	 * @param source Vector of lines in which the contents of the specified file should be inserted
	 * @param position Position in the vector before which the contents of the specified file should be inserted
	 * @return `true` if the file read successfully, `false` otherwise.
	 */
	static bool read(const std::string& filename, std::vector<std::string>* source, std::size_t position);
	
	/**
	 * Join source lines into a single source string.
	 *
	 * @param source Source lines
	 * @return Single string containing entire source
	 */
	static std::string generateSourceBuffer(const std::vector<std::string>& source);
	
	/**
	 * Checks the compile status of a shader.
	 *
	 * @param shader Shader to check
	 * @param[out] log String which will be filled with an error log if compilation failed.
	 * @return `true` if the shader was compiled successfully, `false` otherwise.
	 */
	static bool checkShaderCompileStatus(GLuint shader, std::string* log);
	
	/**
	 * Checks the link status of a shader program.
	 *
	 * @param program Shader program to check
	 * @param[out] log String which will be filled with an error log if linking failed.
	 * @return `true` if the shader was linked successfully, `false` otherwise.
	 */
	static bool checkShaderProgramLinkStatus(GLuint program, std::string* log);
	
	/**
	 * Preprocesses the shader source code. This will replace `#pragma include` directives with the contents of their referenced files and determine which types of shader (vertex, fragment, and geometry) to produce when generating a shader permutation by checking for `#pragma vertex`, `#pragma geometry`, and `#pragma fragment` directives.
	 */
	bool preprocess(const std::string& filename, std::vector<std::string>* source);
	
	/**
	 * Scans a shader permutation for active uniforms and sets up the shader inputs accordingly. This should be called every time a new shader permutation is generated.
	 */
	void reevaluateInputs(ShaderPermutation* permutation);
	
	/**
	 * Reroutes shader inputs to the uniform locations of the active shader permutation.
	 */
	void rerouteInputs();
	
	/**
	 * Deletes all shader inputs
	 */
	void deleteAllInputs();
	
	/**
	 * Links a material to this shader. Every time a new shader permutation is generated or destroyed, the material shader variables will  be reconnected.
	 */
	void linkMaterial(Material* material);
	
	/**
	 * Unlinks a material from this shader.
	 */
	void unlinkMaterial(Material* material);
	
	/**
	 * Reconnects the shader variables of each linked material.
	 */
	void reconnectLinkedMaterials();
	
	std::string sourceFilename;
	std::vector<std::string> source;
	std::size_t permutationDefinitionLine;
	std::size_t shaderTypeDefinitionLine;
	bool hasVertexDirective;
	bool hasGeometryDirective;
	bool hasFragmentDirective;
	std::map<std::uint32_t, ShaderPermutation*> permutations;
	ShaderPermutation* activePermutation;
	std::vector<ShaderInput*> inputs;
	std::map<std::string, std::size_t> inputMap;
	std::list<Material*> materials;
};

inline bool Shader::hasPermutation(std::uint32_t permutation) const
{
	auto it = permutations.find(permutation);
	return (it != permutations.end());
}

inline std::size_t Shader::getInputCount() const
{
	return inputs.size();
}

inline const ShaderInput* Shader::getInput(std::size_t index) const
{
	return inputs[index];
}

inline const ShaderInput* Shader::getInput(const std::string& name) const
{
	auto it = inputMap.find(name);
	if (it != inputMap.end())
	{
		return inputs[it->second];
	}
	
	return nullptr;
}

} // namespace Emergent

#endif // EMERGENT_GRAPHICS_SHADER_HPP
