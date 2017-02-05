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

#include <emergent/graphics/model.hpp>
#include <emergent/graphics/scene-object.hpp>
#include <emergent/graphics/material.hpp>
#include <emergent/graphics/texture.hpp>
#include <emergent/graphics/vertex-format.hpp>
#include <emergent/graphics/gl3w.hpp>
#include <emergent/geometry/winged-edge.hpp>
#include <iostream>
#include <fstream>
#include <streambuf>
#include <cstdint>
#include <sstream>
#include <string>

namespace Emergent
{

Model::Model()
{}

Model::~Model()
{
	destroy();
}

void Model::destroy()
{
	for (auto group: groups)
	{
		glDeleteBuffers(1, &group->ibo);
    	glDeleteBuffers(1, &group->vbo);
    	glDeleteVertexArrays(1, &group->vao);
    	delete group;
    }
	groups.clear();
	groupMap.clear();
    
    for (auto material: materials)
    {
    	delete material;
    }
	materials.clear();
	materialMap.clear();
}

bool Model::create(const WingedEdge* mesh)
{
	destroy();
	
	std::size_t vertexCount = mesh->getTriangles()->size() * 3;
	std::size_t vertexSize = 6; // position, normal
	std::size_t indexCount = mesh->getTriangles()->size() * 3;
	
	// Generate vertex and index data from mesh
	float* vertexData = generateVertexData(mesh);
	std::uint32_t* indexData = generateIndexData(mesh);
	
	// Create and load VAO, VBO, and IBO
	GLuint vao;
	GLuint vbo;
	GLuint ibo;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexSize * vertexCount, vertexData, GL_STATIC_DRAW);
	glEnableVertexAttribArray(EMERGENT_VERTEX_POSITION);
	glVertexAttribPointer(EMERGENT_VERTEX_POSITION, 3, GL_FLOAT, GL_FALSE, vertexSize * sizeof(float), (char*)0 + 0 * sizeof(float));
	glEnableVertexAttribArray(EMERGENT_VERTEX_NORMAL);
	glVertexAttribPointer(EMERGENT_VERTEX_NORMAL, 3, GL_FLOAT, GL_FALSE, vertexSize * sizeof(float), (char*)0 + 3 * sizeof(float));
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(std::uint32_t) * indexCount, indexData, GL_STATIC_DRAW);
	
	// Free vertex and index data
	delete[] vertexData;
	delete[] indexData;
	
	// Create material and model group
	DefaultMaterial* material = new DefaultMaterial();
	Model::Group* group = new Model::Group();
	group->name = "default";
	group->skeleton = nullptr;
	group->material = material;
	group->triangleCount = mesh->getTriangles()->size();
	group->vao = vao;
	group->vbo = vbo;
	group->ibo = ibo;
	
	// Add the material and group to the model
	addMaterial("default", material);
	addGroup(group);
	
	return true;
}

bool Model::load(const std::string& filename)
{
	destroy();
	
	// Open file
	std::ifstream file(filename.c_str());
	if (!file.is_open())
	{
		std::cerr << "Model::load(): Failed to open model file \"" << filename << "\"" << std::endl;
		return false;
	}

	// Read model from file stream
	if (!readMDL(&file, filename))
	{
		std::cerr << "Model::load(): Failed to read model file \"" << filename << "\"" << std::endl;
		file.close();
		return false;
	}

	// Close file
	file.close();

	return true;
}

ModelInstance* Model::createInstance() const
{
	return new ModelInstance(this);
}

void Model::addGroup(Model::Group* group)
{
	auto it = groupMap.find(group->name);
	if (it != groupMap.end())
	{
		std::cerr << "Model::addGroup(): Attempting to add duplicate model group \"" << group->name << "\"\n";
		return;
	}
	
	groups.push_back(group);
	groupMap[group->name] = group;
}

void Model::addMaterial(const std::string& name, Material* material)
{
	auto it = materialMap.find(name);
	if (it != materialMap.end())
	{
		std::cerr << "Model::addMaterial(): Attempting to add duplicate model material \"" << name << "\"\n";
		return;
	}
	
	materials.push_back(material);
	materialMap[name] = material;
}

void Model::setBounds(const AABB& bounds)
{
	this->bounds = bounds;
}

const Model::Group* Model::getGroup(const std::string& name) const
{
	auto it = groupMap.find(name);
	if (it == groupMap.end())
		return nullptr;
	return it->second;
}

Model::Group* Model::getGroup(const std::string& name)
{
	auto it = groupMap.find(name);
	if (it == groupMap.end())
		return nullptr;
	return it->second;
}

const Material* Model::getMaterial(const std::string& name) const
{
	auto it = materialMap.find(name);
	if (it == materialMap.end())
		return nullptr;
	return it->second;
}

Material* Model::getMaterial(const std::string& name)
{
	auto it = materialMap.find(name);
	if (it == materialMap.end())
		return nullptr;
	return it->second;
}

float* Model::generateVertexData(const WingedEdge* mesh)
{
	float* vertexData = new float[mesh->getTriangles()->size() * 3 * 6];
	std::size_t offset = 0;
	
	for (std::size_t i = 0; i < mesh->getTriangles()->size(); ++i)
	{
		const WingedEdge::Triangle* triangle = (*mesh->getTriangles())[i];
		
		const WingedEdge::Vertex* a = triangle->edge->vertex;
		const WingedEdge::Vertex* b = triangle->edge->next->vertex;
		const WingedEdge::Vertex* c = triangle->edge->previous->vertex;
		const Vector3& normal = triangle->normal;
		
		vertexData[offset++] = a->position[0];
		vertexData[offset++] = a->position[1];
		vertexData[offset++] = a->position[2];
		vertexData[offset++] = normal.x;
		vertexData[offset++] = normal.y;
		vertexData[offset++] = normal.z;
		
		vertexData[offset++] = b->position[0];
		vertexData[offset++] = b->position[1];
		vertexData[offset++] = b->position[2];
		vertexData[offset++] = normal.x;
		vertexData[offset++] = normal.y;
		vertexData[offset++] = normal.z;
		
		vertexData[offset++] = c->position[0];
		vertexData[offset++] = c->position[1];
		vertexData[offset++] = c->position[2];
		vertexData[offset++] = normal.x;
		vertexData[offset++] = normal.y;
		vertexData[offset++] = normal.z;
		
		// Calculate smoothed vertex normal
		/*
		Vector3 normal(0.0f);
		WingedEdge::Edge* start = vertex->edge;
		WingedEdge::Edge* e = start;
		do
		{
			normal += e->triangle->normal;
			e = e->previous->symmetric;
		}
		while (e != start && e != nullptr);
		normal = glm::normalize(normal);
		*/
	}
	
	return vertexData;
}

std::uint32_t* Model::generateIndexData(const WingedEdge* mesh)
{
	std::uint32_t* indexData = new std::uint32_t[mesh->getTriangles()->size() * 3];
	std::size_t offset = 0;
	
	for (std::size_t i = 0; i < mesh->getTriangles()->size(); ++i)
	{
		indexData[offset++] = i * 3;
		indexData[offset++] = i * 3 + 1;
		indexData[offset++] = i * 3 + 2;
	}
	
	return indexData;
}

bool Model::readMDL(std::istream* stream, const std::string& filename)
{
	std::string line;

	std::string directoryName;
	std::size_t delimeter = filename.find_last_of("/\\");
	if (delimeter != std::string::npos)
	{
		directoryName = filename.substr(0, delimeter + 1);
	}
	
	AABB bounds;
	std::size_t materialCount = 0;
	std::vector<Material*> materials;
	std::vector<std::string> materialNames;
	std::map<std::string, Material*> materialMap;
	DefaultMaterial* material = nullptr;
	
	std::size_t groupCount = 0;
	std::vector<Model::Group*> groups;
	Model::Group* group = nullptr;
	float* vertexData = nullptr;
	float* vertexElement = nullptr;
	std::size_t vertexCount = 0;
	std::size_t vertexSize = 0;
	std::size_t triangleCount = 0;
	std::size_t indexCount = 0;

	Texture* texture = nullptr;
	
	//std::uint16_t* indexData16 = nullptr;
	std::uint32_t* indexData32 = nullptr;
	std::uint32_t* index32 = nullptr;

	while (stream->good() && std::getline(*stream, line))
	{
		// Tokenize line
		std::vector<std::string> tokens;
		std::string token;
		std::istringstream linestream(line);
		while (linestream >> token)
			tokens.push_back(token);
		
		// Skip empty lines and comments
		if (tokens.empty() || tokens[0][0] == '#')
			continue;
		
		if (tokens[0] == "bounds" && tokens.size() == 7)
		{
			glm::vec3 min;
			glm::vec3 max;
			
			std::stringstream(tokens[1]) >> min.x;
			std::stringstream(tokens[2]) >> min.y;
			std::stringstream(tokens[3]) >> min.z;
			std::stringstream(tokens[4]) >> max.x;
			std::stringstream(tokens[5]) >> max.y;
			std::stringstream(tokens[6]) >> max.z;
			
			if (group != nullptr)
				group->bounds = AABB(min, max);
			else
				bounds = AABB(min, max);
		}
		else if (tokens[0] == "material_count" && tokens.size() == 2)
		{
			std::stringstream(tokens[1]) >> materialCount;
		}
		else if (tokens[0] == "material" && tokens.size() == 2)
		{
			if (materials.size() >= materialCount)
			{
				std::cerr << "Model::readMDL(): Invalid line \"" << line << "\" in file \"" << filename << "\": material count exceeded" << std::endl;
			}
			
			material = new DefaultMaterial();
			materials.push_back(material);
			materialNames.push_back(tokens[1]);
			materialMap[materialNames.back()] = material;
		}
		else if (tokens[0] == "diffuse_color" && tokens.size() == 4)
		{
			glm::vec3 color;
			std::stringstream(tokens[1]) >> color.x;
			std::stringstream(tokens[2]) >> color.y;
			std::stringstream(tokens[3]) >> color.z;
			
			material->diffuseColor = color;
		}
		else if (tokens[0] == "specular_color" && tokens.size() == 4)
		{
			glm::vec3 color;
			std::stringstream(tokens[1]) >> color.x;
			std::stringstream(tokens[2]) >> color.y;
			std::stringstream(tokens[3]) >> color.z;
			
			material->specularColor = color;
		}
		else if (tokens[0] == "emissive_color" && tokens.size() == 4)
		{
			glm::vec3 color;
			std::stringstream(tokens[1]) >> color.x;
			std::stringstream(tokens[2]) >> color.y;
			std::stringstream(tokens[3]) >> color.z;
			
			material->emissiveColor = color;
		}
		else if (tokens[0] == "hardness" && tokens.size() == 2)
		{
			float value;
			std::stringstream(tokens[1]) >> value;
			material->hardness = value;
		}
		else if (tokens[0] == "opacity" && tokens.size() == 2)
		{
			float value;
			std::stringstream(tokens[1]) >> value;
			material->opacity = value;
		}
		else if (tokens[0] == "shadeless" && tokens.size() == 2)
		{
			float value;
			std::stringstream(tokens[1]) >> value;
			material->shadeless = (value == 1.0f);
		}
		else if (tokens[0] == "shadow_caster" && tokens.size() == 2)
		{
			float value;
			std::stringstream(tokens[1]) >> value;
			material->shadowCaster = (value == 1.0f);
		}
		else if (tokens[0] == "shadow_receiver" && tokens.size() == 2)
		{
			float value;
			std::stringstream(tokens[1]) >> value;
			material->shadowReceiver = (value == 1.0f);
		}
		else if (tokens[0] == "texture" && tokens.size() == 2)
		{
			//texture = material->createTexture();
		}
		else if (tokens[0] == "image" && tokens.size() == 2)
		{
			/*
			std::string imageFilename = directoryName + tokens[1];
			GLuint textureID;

			if (!loadTexture(imageFilename, &textureID))
			{
				std::cerr << "Model::readMDL(): Failed to load texture image \"" << imageFilename << "\"" << std::endl;
				continue;
			}

			texture->setTextureID(textureID);
			*/

		}
		else if (tokens[0] == "coordinate_source" && tokens.size() == 2)
		{
			// TODO
		}
		else if (tokens[0] == "coordinate_offset" && tokens.size() == 4)
		{
			/*
			glm::vec3 offset;
			std::stringstream(tokens[1]) >> offset.x;
			std::stringstream(tokens[2]) >> offset.y;
			std::stringstream(tokens[3]) >> offset.z;
			texture->setCoordinateOffset(offset);
			*/
		}
		else if (tokens[0] == "coordinate_scale" && tokens.size() == 4)
		{
			/*
			glm::vec3 scale;
			std::stringstream(tokens[1]) >> scale.x;
			std::stringstream(tokens[2]) >> scale.y;
			std::stringstream(tokens[3]) >> scale.z;
			texture->setCoordinateScale(scale);
			*/
		}
		else if (tokens[0] == "image_extension" && tokens.size() == 2)
		{
			// TODO
		}
		else if (tokens[0] == "interpolation" && tokens.size() == 2)
		{
			// TODO
		}
		else if (tokens[0] == "mipmap" && tokens.size() == 2)
		{
			// TODO
		}
		else if (tokens[0] == "mipmap_interpolation" && tokens.size() == 2)
		{
			// TODO
		}
		else if (tokens[0] == "diffuse_influence" && tokens.size() == 2)
		{
			/*
			float influence;
			std::stringstream(tokens[1]) >> influence;
			texture->setDiffuseInfluence(influence);
			*/
		}
		else if (tokens[0] == "specular_influence" && tokens.size() == 2)
		{
			/*
			float influence;
			std::stringstream(tokens[1]) >> influence;
			texture->setSpecularInfluence(influence);
			*/
		}
		else if (tokens[0] == "emissive_influence" && tokens.size() == 2)
		{
			/*
			float influence;
			std::stringstream(tokens[1]) >> influence;
			texture->setEmissiveInfluence(influence);
			*/
		}
		else if (tokens[0] == "roughness_influence" && tokens.size() == 2)
		{
			/*
			float influence;
			std::stringstream(tokens[1]) >> influence;
			texture->setRoughnessInfluence(influence);
			*/
		}
		else if (tokens[0] == "opacity_influence" && tokens.size() == 2)
		{
			/*
			float influence;
			std::stringstream(tokens[1]) >> influence;
			texture->setOpacityInfluence(influence);
			*/
		}
		else if (tokens[0] == "normal_influence" && tokens.size() == 2)
		{
			/*
			float influence;
			std::stringstream(tokens[1]) >> influence;
			texture->setNormalInfluence(influence);
			*/
		}
		else if (tokens[0] == "group_count" && tokens.size() == 2)
		{
			std::stringstream(tokens[1]) >> groupCount;
		}
		else if (tokens[0] == "group" && tokens.size() == 2)
		{
			if (groups.size() >= groupCount)
			{
				std::cerr << "Model::readMDL(): Invalid line \"" << line << "\" in file \"" << filename << "\": group count exceeded" << std::endl;
			}
			
			if (group != nullptr)
			{
				// Create VAO
				group->triangleCount = triangleCount;
				glGenVertexArrays(1, &group->vao);
				glBindVertexArray(group->vao);
				
				// Generate VBO and upload data
				glGenBuffers(1, &group->vbo);
				glBindBuffer(GL_ARRAY_BUFFER, group->vbo);
				glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexSize * vertexCount, vertexData, GL_STATIC_DRAW);
				
				// Set vertex attribute array
				std::size_t offset = 0;
				if (group->vertexFormat.hasPositions)
				{
					std::size_t attribSize = 3;
					glEnableVertexAttribArray(EMERGENT_VERTEX_POSITION);
					glVertexAttribPointer(EMERGENT_VERTEX_POSITION, attribSize, GL_FLOAT, GL_FALSE, sizeof(float) * vertexSize, (char*)0 + offset * sizeof(GLfloat));
					offset += attribSize;
				}
				if (group->vertexFormat.hasTexcoords)
				{
					std::size_t attribSize = 2;
					glEnableVertexAttribArray(EMERGENT_VERTEX_TEXCOORD);
					glVertexAttribPointer(EMERGENT_VERTEX_TEXCOORD, attribSize, GL_FLOAT, GL_FALSE, sizeof(float) * vertexSize, (char*)0 + offset * sizeof(GLfloat));
					offset += attribSize;
				}
				if (group->vertexFormat.hasNormals)
				{
					std::size_t attribSize = 3;
					glEnableVertexAttribArray(EMERGENT_VERTEX_NORMAL);
					glVertexAttribPointer(EMERGENT_VERTEX_NORMAL, attribSize, GL_FLOAT, GL_FALSE, sizeof(float) * vertexSize, (char*)0 + offset * sizeof(GLfloat));
					offset += attribSize;
				}
				if (group->vertexFormat.hasColors)
				{
					std::size_t attribSize = 3;
					glEnableVertexAttribArray(EMERGENT_VERTEX_COLOR);
					glVertexAttribPointer(EMERGENT_VERTEX_COLOR, attribSize, GL_FLOAT, GL_FALSE, sizeof(float) * vertexSize, (char*)0 + offset * sizeof(GLfloat));
					offset += attribSize;
				}
				if (group->vertexFormat.hasWeights)
				{
					std::size_t attribSize = group->vertexFormat.bonesPerVertex;
					glEnableVertexAttribArray(EMERGENT_VERTEX_BONE_INDICES);
					glVertexAttribPointer(EMERGENT_VERTEX_BONE_INDICES, attribSize, GL_FLOAT, GL_FALSE, sizeof(float) * vertexSize, (char*)0 + offset * sizeof(GLfloat));
					offset += attribSize;
					glEnableVertexAttribArray(EMERGENT_VERTEX_BONE_WEIGHTS);
					glVertexAttribPointer(EMERGENT_VERTEX_BONE_WEIGHTS, attribSize, GL_FLOAT, GL_FALSE, sizeof(float) * vertexSize, (char*)0 + offset * sizeof(GLfloat));
					offset += attribSize;
				}
				
				// Generate IBO and upload data
				glGenBuffers(1, &group->ibo);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, group->ibo);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(std::uint32_t) * indexCount, indexData32, GL_STATIC_DRAW);
				
				group->triangleCount = triangleCount;
				
				delete[] vertexData;
				vertexData = nullptr;
				delete[] indexData32;
				indexData32 = nullptr;
    		}
			
			// Create new group
			group = new Model::Group();
			group->name = tokens[1];
			group->skeleton = nullptr;
			group->material = nullptr;
			group->triangleCount = 0;
			group->vao = 0;
			group->vbo = 0;
			group->ibo = 0;
			groups.push_back(group);
		}
		else if (tokens[0] == "useskl" && tokens.size() == 2)
		{
			// TODO
		}
		else if (tokens[0] == "usemtl" && tokens.size() == 2)
		{
			auto it = materialMap.find(tokens[1]);
			if (it == materialMap.end())
			{
				std::cerr << "Model::readMDL(): Invalid line \"" << line << "\" in file \"" << filename << "\": unknown material" << std::endl;
				continue;
			}
			
			group->material = it->second;
		}
		else if (tokens[0] == "vertex_format")
		{
			for (std::size_t i = 1; i < tokens.size(); ++i)
			{
				if (tokens[i] == "position")
					group->vertexFormat.hasPositions = true;
				else if (tokens[i] == "uv")
					group->vertexFormat.hasTexcoords = true;
				else if (tokens[i] == "normal")
					group->vertexFormat.hasNormals = true;
				else if (tokens[i] == "color")
					group->vertexFormat.hasColors = true;
				else if (tokens[i] == "weights")
				{
					group->vertexFormat.hasWeights = true;
					std::stringstream(tokens[++i]) >> group->vertexFormat.bonesPerVertex;
				}
			}
			
			vertexSize = 0;
			if (group->vertexFormat.hasPositions)
				vertexSize += 3;
			if (group->vertexFormat.hasTexcoords)
				vertexSize += 2;
			if (group->vertexFormat.hasNormals)
				vertexSize += 3;
			if (group->vertexFormat.hasColors)
				vertexSize += 3;
			if (group->vertexFormat.hasWeights)
				vertexSize += group->vertexFormat.bonesPerVertex * 2;
		}
		else if (tokens[0] == "vertex_count" && tokens.size() == 2)
		{
			std::stringstream(tokens[1]) >> vertexCount;
			vertexData = new float[vertexCount * vertexSize];
			vertexElement = &vertexData[0];
		}
		else if (tokens[0] == "v" && tokens.size() == vertexSize + 1)
		{
			for (std::size_t i = 0; i < vertexSize; ++i)
				std::stringstream(tokens[i + 1]) >> *(vertexElement++);
		}
		else if (tokens[0] == "face_count" && tokens.size() == 2)
		{
			std::stringstream(tokens[1]) >> triangleCount;
			indexCount = triangleCount * 3;
			indexData32 = new std::uint32_t[indexCount];
			index32 = &indexData32[0];
		}
		else if (tokens[0] == "f" && tokens.size() == 4)
		{
			std::stringstream(tokens[1]) >> *(index32++);
			std::stringstream(tokens[2]) >> *(index32++);
			std::stringstream(tokens[3]) >> *(index32++);
		}
		else
		{
			std::cerr << "Model::readMDL(): Invalid line \"" << line << "\" in file \"" << filename << "\"" << std::endl;
			continue;
		}
	}
	
	// Create VAO
	group->triangleCount = triangleCount;
	glGenVertexArrays(1, &group->vao);
	glBindVertexArray(group->vao);
	
	// Generate VBO and upload data
	glGenBuffers(1, &group->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, group->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexSize * vertexCount, vertexData, GL_STATIC_DRAW);
	
	// Set vertex attribute array
	std::size_t offset = 0;
	if (group->vertexFormat.hasPositions)
	{
		std::size_t attribSize = 3;
		glEnableVertexAttribArray(EMERGENT_VERTEX_POSITION);
		glVertexAttribPointer(EMERGENT_VERTEX_POSITION, attribSize, GL_FLOAT, GL_FALSE, sizeof(float) * vertexSize, (char*)0 + offset * sizeof(GLfloat));
		offset += attribSize;
	}
	if (group->vertexFormat.hasTexcoords)
	{
		std::size_t attribSize = 2;
		glEnableVertexAttribArray(EMERGENT_VERTEX_TEXCOORD);
		glVertexAttribPointer(EMERGENT_VERTEX_TEXCOORD, attribSize, GL_FLOAT, GL_FALSE, sizeof(float) * vertexSize, (char*)0 + offset * sizeof(GLfloat));
		offset += attribSize;
	}
	if (group->vertexFormat.hasNormals)
	{
		std::size_t attribSize = 3;
		glEnableVertexAttribArray(EMERGENT_VERTEX_NORMAL);
		glVertexAttribPointer(EMERGENT_VERTEX_NORMAL, attribSize, GL_FLOAT, GL_FALSE, sizeof(float) * vertexSize, (char*)0 + offset * sizeof(GLfloat));
		offset += attribSize;
	}
	if (group->vertexFormat.hasColors)
	{
		std::size_t attribSize = 3;
		glEnableVertexAttribArray(EMERGENT_VERTEX_COLOR);
		glVertexAttribPointer(EMERGENT_VERTEX_COLOR, attribSize, GL_FLOAT, GL_FALSE, sizeof(float) * vertexSize, (char*)0 + offset * sizeof(GLfloat));
		offset += attribSize;
	}
	if (group->vertexFormat.hasWeights)
	{
		std::size_t attribSize = group->vertexFormat.bonesPerVertex;
		glEnableVertexAttribArray(EMERGENT_VERTEX_BONE_INDICES);
		glVertexAttribPointer(EMERGENT_VERTEX_BONE_INDICES, attribSize, GL_FLOAT, GL_FALSE, sizeof(float) * vertexSize, (char*)0 + offset * sizeof(GLfloat));
		offset += attribSize;
		glEnableVertexAttribArray(EMERGENT_VERTEX_BONE_WEIGHTS);
		glVertexAttribPointer(EMERGENT_VERTEX_BONE_WEIGHTS, attribSize, GL_FLOAT, GL_FALSE, sizeof(float) * vertexSize, (char*)0 + offset * sizeof(GLfloat));
		offset += attribSize;
	}
	
	// Generate IBO and upload data
	glGenBuffers(1, &group->ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, group->ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(std::uint32_t) * indexCount, indexData32, GL_STATIC_DRAW);
	
	group->triangleCount = triangleCount;
	
	delete[] vertexData;
	vertexData = nullptr;
	delete[] indexData32;
	indexData32 = nullptr;
	
	// Set bounds
	setBounds(bounds);
	
	// Add materials to model
	for (std::size_t i = 0; i < materials.size(); ++i)
		addMaterial(materialNames[i], materials[i]);
	
	// Add groups to model
	for (std::size_t i = 0; i < groups.size(); ++i)
		addGroup(groups[i]);
	
	return true;
}

} // namespace Emergent
