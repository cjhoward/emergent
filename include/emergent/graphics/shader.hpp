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
#include <cstdlib>
#include <vector>
#include <string>

namespace Emergent
{

/**
 * @ingroup graphics
 */
enum class ShaderParameter
{
	MODEL_MATRIX,
	MODEL_VIEW_MATRIX,
	MODEL_VIEW_PROJECTION_MATRIX,
	NORMAL_MODEL_MATRIX,
	NORMAL_MODEL_VIEW_MATRIX,
	CAMERA_DIRECTION,
	
	// Clipping
	CLIPPING_PLANES,
	
	// Skinning
	BONE_MATRICES,
	
	// Material
	MATERIAL_DIFFUSE_COLOR,
	MATERIAL_SPECULAR_COLOR,
	MATERIAL_EMISSIVE_COLOR,
	MATERIAL_ROUGHNESS,
	MATERIAL_OPACITY,
	
	// Texture
	MATERIAL_TEXTURE,
	TEXCOORD_OFFSET,
	TEXCOORD_SCALE,
	TEXTURE_DIFFUSE_INFLUENCE,
	TEXTURE_SPECULAR_INFLUENCE,
	TEXTURE_EMISSIVE_INFLUENCE,
	TEXTURE_ROUGHNESS_INFLUENCE,
	TEXTURE_OPACITY_INFLUENCE,
	TEXTURE_NORMAL_INFLUENCE,
	
	// Lighting
	POINT_LIGHT_COLOR,
	POINT_LIGHT_POSITION,
	POINT_LIGHT_ATTENUATION,
	DIRECTIONAL_LIGHT_COLOR,
	DIRECTIONAL_LIGHT_DIRECTION,
	SPOTLIGHT_COLOR,
	SPOTLIGHT_POSITION,
	SPOTLIGHT_ATTENUATION,
	SPOTLIGHT_DIRECTION,
	SPOTLIGHT_CUTOFF,
	SPOTLIGHT_EXPONENT,
	DIFFUSE_ENVIRONMENT_MAP,
	SPECULAR_ENVIRONMENT_MAP,
	
	// Shadows
	MODEL_VIEW_PROJECTION_BIAS_MATRIX,
	SHADOW_MAP,
	TREE_SHADOW,
	
	TIME,
	
	// DO NOT PASS
	COUNT
};

/**
 * @ingroup graphics
 */
class ShaderParameterSet
{
public:
	ShaderParameterSet();	
	
	bool hasParameter(ShaderParameter parameter) const;
	
	// Sets a parameter location
	void setLocation(ShaderParameter parameter, GLint location);
	
	// Sets a parameter value
	void setValue(ShaderParameter parameter, int value);
	void setValue(ShaderParameter parameter, float value);
	void setValue(ShaderParameter parameter, const Vector2& value);
	void setValue(ShaderParameter parameter, const Vector3& value);
	void setValue(ShaderParameter parameter, const Vector4& value);
	void setValue(ShaderParameter parameter, const Matrix3& value);
	void setValue(ShaderParameter parameter, const Matrix4& value);
	
	// Sets a single value within an array parameter
	void setValue(ShaderParameter parameter, std::size_t index, int value);
	void setValue(ShaderParameter parameter, std::size_t index, float value);
	void setValue(ShaderParameter parameter, std::size_t index, const Vector2& value);
	void setValue(ShaderParameter parameter, std::size_t index, const Vector3& value);
	void setValue(ShaderParameter parameter, std::size_t index, const Vector4& value);
	void setValue(ShaderParameter parameter, std::size_t index, const Matrix3& value);
	void setValue(ShaderParameter parameter, std::size_t index, const Matrix4& value);
	
	// Sets multiple values within an array parameter
	void setValue(ShaderParameter parameter, std::size_t index, const int* values, std::size_t count);
	void setValue(ShaderParameter parameter, std::size_t index, const float* values, std::size_t count);
	void setValue(ShaderParameter parameter, std::size_t index, const Vector2* values, std::size_t count);
	void setValue(ShaderParameter parameter, std::size_t index, const Vector3* values, std::size_t count);
	void setValue(ShaderParameter parameter, std::size_t index, const Vector4* values, std::size_t count);
	void setValue(ShaderParameter parameter, std::size_t index, const Matrix3* values, std::size_t count);
	void setValue(ShaderParameter parameter, std::size_t index, const Matrix4* values, std::size_t count);
	
private:
	GLint locations[static_cast<std::size_t>(ShaderParameter::COUNT)];
};

inline bool ShaderParameterSet::hasParameter(ShaderParameter parameter) const
{
	return (locations[static_cast<std::size_t>(parameter)] != -1);
}

/**
 * @ingroup graphics
 */
class Shader
{
public:
	~Shader();
	ShaderParameterSet* getParameters();
	
	void bind() const;

private:
	friend class ShaderLoader;
	
	Shader();
	void detectParameters();
	
	GLuint shaderProgram;
	GLuint vertexShader;
	GLuint fragmentShader;
	
	ShaderParameterSet parameters;
};

inline ShaderParameterSet* Shader::getParameters()
{
	return &parameters;
}

/**
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
	 */
	Shader* load(const std::string& filename) const;

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

#endif // EMERGENT_GRAPHICS_SHADER_HPP

