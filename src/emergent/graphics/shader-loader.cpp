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

#include <emergent/graphics/shader-loader.hpp>
#include <emergent/graphics/shader.hpp>
#include <emergent/graphics/shader-parameter-set.hpp>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <iostream>

namespace Emergent
{

void ShaderLoader::define(const std::string& name)
{
	std::stringstream stream;
	stream << "#define " << name << '\n';
	definitions.push_back(stream.str());
}

void ShaderLoader::define(const std::string& name, int value)
{
	std::stringstream stream;
	stream << "#define " << name << " " << value << '\n';
	definitions.push_back(stream.str());
}

void ShaderLoader::define(const std::string& name, float value)
{
	std::stringstream stream;
	stream << "#define " << name << " " << value << '\n';
	definitions.push_back(stream.str());
}

void ShaderLoader::define(const std::string& name, const std::string& value)
{
	std::stringstream stream;
	stream << "#define " << name << " " << value << '\n';
	definitions.push_back(stream.str());
}

void ShaderLoader::undefine()
{
	definitions.clear();
}

Shader* ShaderLoader::load(const std::string& filename, const ShaderParameterSet* parameterSet) const
{
	GLuint shaderProgram;
	GLuint vertexShader;
	GLuint fragmentShader;
	
	// Load vertex shader
	if (!loadShader(filename, &vertexShader, GL_VERTEX_SHADER))
	{
		std::cerr << "Failed to load vertex shader \"" << filename << "\"" << std::endl;
		return nullptr;
	}
	
	// Load fragment shader
	if (!loadShader(filename, &fragmentShader, GL_FRAGMENT_SHADER))
	{
		std::cerr << "Failed to load fragment shader \"" << filename << "\"" << std::endl;
		glDeleteShader(vertexShader);
		return nullptr;
	}
	
    // Create shader program and attach shaders
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    // Link shader program
    glLinkProgram(shaderProgram);
    
    // Check shader program link status
    std::string log;
    if (!checkProgramLinkStatus(shaderProgram, &log))
	{
        std::cerr << "Failed to link shader program \"" << filename << "\": " << log << std::endl;
		glDetachShader(shaderProgram, vertexShader);
		glDetachShader(shaderProgram, fragmentShader);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		glDeleteProgram(shaderProgram);
        return nullptr;
    }
	
	// Create shader
	Shader* shader = new Shader();
	shader->shaderProgram = shaderProgram;
	shader->vertexShader = vertexShader;
	shader->fragmentShader = fragmentShader;
	
	// Find shader parameters
	shader->parameterSet = parameterSet;
	shader->parameterLocations.resize(parameterSet->getParameterCount());
	for (std::size_t i = 0; i < parameterSet->getParameterCount(); ++i)
	{
		shader->parameterLocations[i] = glGetUniformLocation(shaderProgram, parameterSet->getParameter(i)->getName().c_str());
	}
	
	return shader;
}

bool ShaderLoader::checkShaderCompileStatus(GLuint shader, std::string* log)
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

bool ShaderLoader::checkProgramLinkStatus(GLuint program, std::string* log)
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

bool ShaderLoader::loadShader(const std::string& filename, GLuint* shader, GLenum shaderType) const
{
	// Temporarily define the current shader type
	if (shaderType == GL_VERTEX_SHADER)
	{
		definitions.push_back("#define _VERTEX_SHADER");
	}
	else if (shaderType == GL_FRAGMENT_SHADER)
	{
		definitions.push_back("#define _FRAGMENT_SHADER");
	}
	else if (shaderType == GL_GEOMETRY_SHADER)
	{
		definitions.push_back("#define _GEOMETRY_SHADER");
	}
	
	// Load shader source
	std::string source;
	if (!loadSource(filename, &source))
	{
		std::cerr << "Failed to load shader source \"" << filename << "\"" << std::endl;
		definitions.pop_back();
		return false;
	}
	
	// Remove temporary definition
	definitions.pop_back();
	
	// Create shader object
	*shader = glCreateShader(shaderType);
	
	// Attach shader source
	const char* c_str = source.c_str();
	glShaderSource(*shader, 1, &c_str, nullptr);
	
	// Compile shader source
	glCompileShader(*shader);
	
	// Check compilation status
	std::string log;
	if (!checkShaderCompileStatus(*shader, &log))
	{
		std::cerr << "Failed to compile shader \"" << filename << "\": " << log << std::endl;
		glDeleteShader(*shader);
		return false;
	}
	
	return true;
}

bool ShaderLoader::loadSource(const std::string& filename, std::string* source) const
{
	std::vector<std::string> sourceLines;
	
	// Read source file
	if (!readSource(filename, &sourceLines))
	{
		std::cerr << "Failed to read shader source file \"" << filename << "\"" << std::endl;
		return false;
	}
	
	// Preprocess source
	if (!preprocess(filename, &sourceLines))
	{
		std::cerr << "Failed to preprocess shader source file \"" << filename << "\"" << std::endl;
		return false;
	}
	
	// Join source lines into single source string
	std::ostringstream sourceStream;
	std::copy(sourceLines.begin(),
		sourceLines.end(),
		std::ostream_iterator<std::string>(sourceStream, "\n"));
	*source = sourceStream.str();
	
	return true;
}

bool ShaderLoader::readSource(const std::string& filename, std::vector<std::string>* sourceLines) const
{
	std::ifstream file(filename.c_str());
	if (!file)
	{
		return false;
	}
	
	// Read file lines into vector
	std::string line;
	while (std::getline(file, line))
		sourceLines->push_back(line);
	
	return true;
}

bool ShaderLoader::preprocess(const std::string& filename, std::vector<std::string>* sourceLines) const
{
	// Determine base path
	std::string basePath;
	std::size_t delimeterIndex;
	delimeterIndex = filename.find_last_of("/\\");
	if (delimeterIndex != std::string::npos)
	{
		basePath = filename.substr(0, delimeterIndex + 1);
	}
	
	std::size_t lineIndex = 0;
	while (lineIndex < sourceLines->size())
	{
		const std::string& line = (*sourceLines)[lineIndex];
		
		std::vector<std::string> tokens;
		std::string token;
		std::istringstream linestream(line);
		while (linestream >> token)
			tokens.push_back(token);
		
		if (tokens.empty())
		{
			++lineIndex;
		}
		else if (tokens[0] == "#version")
		{
			// Insert definitions after version directive
			sourceLines->insert(sourceLines->begin() + lineIndex + 1, definitions.begin(), definitions.end());
			++lineIndex;
		}
		else if (tokens[0] == "#include")
		{
			std::string includeFilename = basePath + tokens[1].substr(1, tokens[1].length() - 2);
			
			// Read include file source
			std::vector<std::string> includeLines;
			if (!readSource(includeFilename, &includeLines))
			{
				std::cerr << "Failed to include shader source file \"" << includeFilename << "\" from \"" << filename << "\"" << std::endl;
				return false;
			}
			
			// Insert include file source at current position
			sourceLines->erase(sourceLines->begin() + lineIndex);
			sourceLines->insert(sourceLines->begin() + lineIndex, includeLines.begin(), includeLines.end());
		}
		else
		{
			++lineIndex;
		}
	}
	
	return true;
}

} // namespace Emergent
