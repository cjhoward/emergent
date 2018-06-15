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

#include <emergent/graphics/shader.hpp>
#include <emergent/graphics/material.hpp>
#include <emergent/graphics/shader-variable.hpp>
#include <emergent/graphics/shader-input.hpp>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>

namespace Emergent
{

ShaderPermutation::ShaderPermutation(std::uint32_t permutationValue, GLuint shaderProgram, GLuint vertexShader, GLuint geometryShader, GLuint fragmentShader):
	permutationValue(permutationValue),
	shaderProgram(shaderProgram),
	vertexShader(vertexShader),
	geometryShader(geometryShader),
	fragmentShader(fragmentShader)
{}

ShaderPermutation::~ShaderPermutation()
{
	if (vertexShader != 0)
	{
		glDetachShader(shaderProgram, vertexShader);
		glDeleteShader(vertexShader);
	}
	
	if (geometryShader != 0)
	{
		glDetachShader(shaderProgram, geometryShader);
		glDeleteShader(geometryShader);
	}
	
	if (fragmentShader != 0)
	{
		glDetachShader(shaderProgram, fragmentShader);
		glDeleteShader(fragmentShader);
	}
	
	glDeleteProgram(shaderProgram);
}

Shader::Shader()
{}

Shader::~Shader()
{
	deleteAllInputs();
	deleteAllPermutations();
}

bool Shader::loadSource(const std::string& filename)
{
	// If shader has already been loaded
	if (!source.empty())
	{
		// Unload shader
		source.clear();
		deleteAllPermutations();
		activePermutation = nullptr;
	}
	
	// Reset preprocessor data
	permutationDefinitionLine = 0;
	shaderTypeDefinitionLine = 0;
	hasVertexDirective = false;
	hasGeometryDirective = false;
	hasFragmentDirective = false;
	
	// Set source filename
	sourceFilename = filename;
	
	// Attempt to read the shader source file
	if (!read(filename, &source, 0))
	{
		return false;
	}
	
	// Attempt to preprocess the shader source
	if (!preprocess(filename, &source))
	{
		source.clear();
		return false;
	}
	
	return true;
}

bool Shader::generatePermutation(std::uint32_t permutation)
{
	if (hasPermutation(permutation))
	{
		return false;
	}
	
	GLuint shaderProgram = 0;
	GLuint vertexShader = 0;
	GLuint geometryShader = 0;
	GLuint fragmentShader = 0;
	bool error = false;
	
	// Create shader program
	shaderProgram = glCreateProgram();
	
	// Inject `__PERMUTATION__` definition
	std::stringstream stream;
	stream << "#define __PERMUTATION__ " << permutation;
	source[permutationDefinitionLine] = stream.str();
	
	// Generate vertex shader
	if (hasVertexDirective)
	{
		// Inject `__VERTEX__` definition
		source[shaderTypeDefinitionLine] = "#define __VERTEX__";
		
		// Convert source lines into single string
		std::string sourceBuffer = generateSourceBuffer(source);
		const char* c_str = sourceBuffer.c_str();
		
		// Compile source into vertex shader
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &c_str, nullptr);
		glCompileShader(vertexShader);

		// Check compilation status
		std::string log;
		if (!checkShaderCompileStatus(vertexShader, &log))
		{
			std::cerr << "Failed to compile vertex shader from \"" << sourceFilename << "\": " << log << std::endl;
			glDeleteShader(vertexShader);
			vertexShader = 0;
			error = true;
		}
		else
		{
			// Attach vertex shader to shader program
			glAttachShader(shaderProgram, vertexShader);
		}
	}
	
	// Generate geometry shader
	if (hasGeometryDirective)
	{
		// Inject `__GEOMETRY__` definition
		source[shaderTypeDefinitionLine] = "#define __GEOMETRY__";
		
		// Convert source lines into single string
		std::string sourceBuffer = generateSourceBuffer(source);
		const char* c_str = sourceBuffer.c_str();
		
		// Compile source into geometry shader
		geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geometryShader, 1, &c_str, nullptr);
		glCompileShader(geometryShader);
		
		// Check compilation status
		std::string log;
		if (!checkShaderCompileStatus(geometryShader, &log))
		{
			std::cerr << "Failed to compile geometry shader from \"" << sourceFilename << "\": " << log << std::endl;
			glDeleteShader(geometryShader);
			geometryShader = 0;
			error = true;
		}
		else
		{
			// Attach geometry shader to shader program
			glAttachShader(shaderProgram, geometryShader);
		}
	}
	
	// Generate fragment shader
	if (hasFragmentDirective)
	{
		// Inject `__FRAGMENT__` definition
		source[shaderTypeDefinitionLine] = "#define __FRAGMENT__";
		
		// Convert source lines into single string
		std::string sourceBuffer = generateSourceBuffer(source);
		const char* c_str = sourceBuffer.c_str();
		
		// Compile source into fragment shader
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &c_str, nullptr);
		glCompileShader(fragmentShader);

		// Check compilation status
		std::string log;
		if (!checkShaderCompileStatus(fragmentShader, &log))
		{
			std::cerr << "Failed to compile fragment shader from \"" << sourceFilename << "\": " << log << std::endl;
			glDeleteShader(fragmentShader);
			fragmentShader = 0;
			error = true;
		}
		else
		{
			// Attach fragment shader to shader program
			glAttachShader(shaderProgram, fragmentShader);
		}
	}
	
	if (error)
	{
		// A shader compilation error occurred, delete all shaders and the shader program
		if (vertexShader != 0)
			glDeleteShader(vertexShader);
		if (geometryShader != 0)
			glDeleteShader(geometryShader);
		if (fragmentShader != 0)
			glDeleteShader(fragmentShader);
		glDeleteProgram(shaderProgram);
		
		return false;
	}

	// Link shader program
	glLinkProgram(shaderProgram);
	
	// Check shader program link status
	std::string log;
	if (!checkShaderProgramLinkStatus(shaderProgram, &log))
	{
		// A shader program linking error occurred, detach and delete all shaders and delete the shader program
		std::cerr << "Failed to link shader program \"" << sourceFilename << "\": " << log << std::endl;
		if (vertexShader != 0)
		{
			glDetachShader(shaderProgram, vertexShader);
			glDeleteShader(vertexShader);
		}
		if (geometryShader != 0)
		{
			glDetachShader(shaderProgram, geometryShader);
			glDeleteShader(geometryShader);
		}
		if (fragmentShader != 0)
		{
			glDetachShader(shaderProgram, fragmentShader);
			glDeleteShader(fragmentShader);
		}
		
		glDeleteProgram(shaderProgram);
		
		return false;
	}
	
	// Allocate shader permutation
	ShaderPermutation* shaderPermutation = new ShaderPermutation(permutation, shaderProgram, vertexShader, geometryShader, fragmentShader);
	for (std::size_t i = 0; i < inputs.size(); ++i)
	{
		shaderPermutation->uniformLocations.push_back(-1);
	}
	
	// Insert shader permutation into map
	permutations.insert(std::pair<std::uint32_t, ShaderPermutation*>(permutation, shaderPermutation));
	
	// Re-evaluate shader inputs
	reevaluateInputs(shaderPermutation);
	
	return true;
}

void Shader::deleteAllPermutations()
{
	// Delete shader permutations
	for (auto it = permutations.begin(); it != permutations.end(); ++it)
	{
		delete it->second;
	}
	permutations.clear();
	
	// Reset active permutation
	activePermutation = nullptr;
	
	// Delete all shader inputs
	deleteAllInputs();
}

bool Shader::activate(std::uint32_t permutation)
{
	// Search for shader permutation
	auto it = permutations.find(permutation);
	if (it == permutations.end())
	{
		return false;
	}
	
	// Bind shader permutation and set as active permutation
	activePermutation = it->second;
	glUseProgram(activePermutation->shaderProgram);
	
	// Reroute shader inputs to point to the active permutation's uniform locations.
	rerouteInputs();
	
	return true;
}

bool Shader::read(const std::string& filename, std::vector<std::string>* source, std::size_t position)
{
	// Attempt to open file
	std::ifstream file(filename.c_str());
	if (!file)
	{
		return false;
	}
	
	// Read file lines into vector
	std::string line;
	while (std::getline(file, line))
	{
		source->insert(source->begin() + position, line);
		++position;
	}
	
	return true;
}

std::string Shader::generateSourceBuffer(const std::vector<std::string>& source)
{
	std::ostringstream stream;
	std::copy(source.begin(), source.end(), std::ostream_iterator<std::string>(stream, "\n"));
	return stream.str();
}

bool Shader::checkShaderCompileStatus(GLuint shader, std::string* log)
{
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		// Determine info log length
		GLint length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

		// Populate log string
		log->resize(length);
		glGetShaderInfoLog(shader, length, &length, &((*log)[0]));

		return false;
	}

	return true;
}

bool Shader::checkShaderProgramLinkStatus(GLuint program, std::string* log)
{
	GLint status;
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		// Determine info log length
		GLint length;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);

		// Populate log string
		log->resize(length);
		glGetProgramInfoLog(program, length, &length, &((*log)[0]));

		return false;
	}

	return true;
}

bool Shader::preprocess(const std::string& filename, std::vector<std::string>* source)
{
	// Determine directory path
	std::string directoryPath;
	std::size_t delimeterIndex;
	delimeterIndex = filename.find_last_of("/\\");
	if (delimeterIndex != std::string::npos)
	{
		directoryPath = filename.substr(0, delimeterIndex + 1);
	}
	
	// For each line in the source
	std::size_t lineIndex = 0;
	while (lineIndex < source->size())
	{
		// Get string containing current line
		const std::string& line = (*source)[lineIndex];
		
		// Tokenize line
		std::vector<std::string> tokens;
		std::string token;
		std::istringstream linestream(line);
		while (linestream >> token)
			tokens.push_back(token);
		
		if (!tokens.empty() && tokens[0][0] == '#')
		{
			if (tokens[0] == "#version")
			{
				// Inject macros immediately following `#version` directive
				permutationDefinitionLine = lineIndex + 1;
				shaderTypeDefinitionLine = lineIndex + 2;
				source->insert(source->begin() + permutationDefinitionLine, std::string());
				source->insert(source->begin() + shaderTypeDefinitionLine, std::string());
				lineIndex += 2;
			}
			else if (tokens[0] == "#pragma" && tokens.size() > 1)
			{
				if (tokens[1] == "include")
				{
					if (tokens.size() == 3)
					{
						// Construct path to include file
						std::string includeFilename = directoryPath + tokens[2].substr(1, tokens[2].length() - 2);
						
						// Erase current line
						source->erase(source->begin() + lineIndex);
						
						// Read include file into sources
						if (!read(includeFilename, source, lineIndex))
						{
							std::cerr << "Failed to include file \"" << includeFilename << "\" from shader \"" << filename << "\"" << std::endl;
							return false;
						}
						
						// Process current line again
						continue;
					}
					else
					{
						std::cerr << "Invalid preprocessor include directive: \"" << line << "\" from shader \"" << filename << "\"" << std::endl;
						return false;
					}
				}
				else if (tokens[1] == "vertex")
				{
					hasVertexDirective = true;
				}
				else if (tokens[1] == "geometry")
				{
					hasGeometryDirective = true;
				}
				else if (tokens[1] == "fragment")
				{
					hasFragmentDirective = true;
				}
			}
		}
		
		++lineIndex;
	}
	
	return true;
}

void Shader::reevaluateInputs(ShaderPermutation* permutation)
{
	// Get maximum uniform name length
	GLint maxUniformNameLength = 0;
	glGetProgramiv(permutation->shaderProgram, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxUniformNameLength);
	
	// Allocate uniform name buffer
	GLchar* uniformName = new GLchar[maxUniformNameLength];
	
	// Get number of active uniforms in the shader
	GLint activeUniformCount = 0;
	glGetProgramiv(permutation->shaderProgram, GL_ACTIVE_UNIFORMS, &activeUniformCount);
	
	// Set first available texture unit
	int availableTextureUnit = 0;
	
	// For each active uniform
	for (GLuint uniformIndex = 0; uniformIndex < activeUniformCount; ++uniformIndex)
	{
		// Get information about uniform
		GLsizei uniformNameLength;
		GLint uniformSize;
		GLenum uniformType;
		glGetActiveUniform(permutation->shaderProgram, uniformIndex, static_cast<GLsizei>(maxUniformNameLength), &uniformNameLength, &uniformSize, &uniformType, &uniformName[0]);
		
		// Get name without array symbols
		std::string inputName = uniformName;
		std::size_t bracketPos = inputName.find_first_of("[");
		if (bracketPos != std::string::npos)
		{
			inputName = inputName.substr(0, bracketPos);
		}
		
		// Determine corresponding shader variable data type
		ShaderVariableType variableType;
		int textureUnit = -1;
		bool unsupported = false;
		switch (uniformType)
		{
			case GL_INT:
				variableType = ShaderVariableType::INT;
				break;
				
			case GL_FLOAT:
				variableType = ShaderVariableType::FLOAT;
				break;
			
			case GL_FLOAT_VEC2:
				variableType = ShaderVariableType::VECTOR_2;
				break;
			
			case GL_FLOAT_VEC3:
				variableType = ShaderVariableType::VECTOR_3;
				break;
			
			case GL_FLOAT_VEC4:
				variableType = ShaderVariableType::VECTOR_4;
				break;
			
			case GL_FLOAT_MAT3:
				variableType = ShaderVariableType::MATRIX_3;
				break;
			
			case GL_FLOAT_MAT4:
				variableType = ShaderVariableType::MATRIX_4;
				break;
			
			case GL_SAMPLER_2D:
			case GL_SAMPLER_2D_SHADOW:
				variableType = ShaderVariableType::TEXTURE_2D;
				textureUnit = availableTextureUnit;
				availableTextureUnit += uniformSize;
				break;
			
			case GL_SAMPLER_CUBE:
				variableType = ShaderVariableType::TEXTURE_CUBE;
				textureUnit = availableTextureUnit;
				availableTextureUnit += uniformSize;
				break;
			
			default:
				unsupported = true;
				break;
		}
		
		// Check if data type is supported
		if (unsupported)
		{
			std::cerr << "Shader uniform \"" << uniformName << "\" from shader \"" << sourceFilename << "\" has an unsupported data type." << std::endl;
			continue;
		}
		
		// Get uniform location
		GLint uniformLocation = glGetUniformLocation(permutation->shaderProgram, uniformName);
		if (uniformLocation == -1)
		{
			std::cerr << "Unable to get location for uniform \"" << uniformName << "\" from shader \"" << sourceFilename << "\"" << std::endl;
			continue;
		}
		
		// Check if shader input with the same name exists
		auto it = inputMap.find(inputName);
		if (it != inputMap.end())
		{
			// Shader input with the same name already exists
			ShaderInput* input = inputs[it->second];
			
			if (variableType != input->getDataType() || uniformSize != input->getElementCount())
			{
				std::cerr << "Shader permutation uniform \"" << uniformName << "\" in shader \"" << sourceFilename << "\" has differing type or size from preceding permutation. The shader input will not be connected." << std::endl;
			}
			else
			{
				permutation->uniformLocations[input->inputIndex] = uniformLocation;
			}
		}
		else
		{
			// Create new shader input
			ShaderInput* input = new ShaderInput(this, inputs.size(), uniformLocation, inputName, variableType, uniformSize, textureUnit);
			inputMap[inputName] = inputs.size();
			inputs.push_back(input);
			
			// Extend the uniform locations of each shader permutation
			for (auto it2 = permutations.begin(); it2 != permutations.end(); ++it2)
			{
				if (it2->second == permutation)
				{
					it2->second->uniformLocations.push_back(uniformLocation);
				}
				else
				{
					// Permutation doesn't have this shader input
					it2->second->uniformLocations.push_back(-1);
				}
			}
		}
	}
	
	// Free uniform name buffer
	delete[] uniformName;
}

void Shader::rerouteInputs()
{
	if (activePermutation != nullptr)
	{
		for (std::size_t i = 0; i < inputs.size(); ++i)
		{
			inputs[i]->uniformLocation = activePermutation->uniformLocations[i];
		}
	}
	else
	{
		for (std::size_t i = 0; i < inputs.size(); ++i)
		{
			inputs[i]->uniformLocation = -1;
		}
	}
}

void Shader::deleteAllInputs()
{
	for (auto it = inputs.begin(); it != inputs.end(); ++it)
	{
		delete (*it);
	}
	
	inputs.clear();
	inputMap.clear();
}

void Shader::linkMaterial(Material* material)
{
	materials.push_back(material);
}

void Shader::unlinkMaterial(Material* material)
{
	materials.remove(material);
}

void Shader::reconnectLinkedMaterials()
{
	for (Material* material: materials)
	{
		material->reconnectVariables();
	}
}

} // namespace Emergent
