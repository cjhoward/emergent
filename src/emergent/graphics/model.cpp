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

#include <emergent/graphics/model.hpp>
#include <emergent/graphics/skeleton.hpp>
#include <emergent/graphics/model-instance.hpp>
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

Model::Model():
	vertexFormat(0),
	vao(0),
	vbo(0),
	ibo(0),
	skeleton(nullptr)
{}

Model::~Model()
{
	destroy();
}

void Model::destroy()
{
	if (vao != 0)
	{
		glDeleteBuffers(1, &ibo);
		glDeleteBuffers(1, &vbo);
		glDeleteVertexArrays(1, &vao);
		
		vertexFormat = 0;
		ibo = 0;
		vbo = 0;
		vao = 0;
	}
	
	if (skeleton != nullptr)
	{
		delete skeleton;
		skeleton = nullptr;
	}

	for (auto group: groups)
	{
    	delete group;
    }
	groups.clear();
	groupMap.clear();
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
	
	// Create model group
	Model::Group* group = new Model::Group();
	group->name = "default";
	group->material = nullptr;
	group->indexOffset = 0;
	group->triangleCount = mesh->getTriangles()->size();
	
	// Add group to the model
	addGroup(group);
	
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

void Model::setVertexFormat(std::uint32_t vertexFormat)
{
	this->vertexFormat = vertexFormat;
}

void Model::setVAO(GLuint vao)
{
	this->vao = vao;
}

void Model::setVBO(GLuint vbo)
{
	this->vbo = vbo;
}

void Model::setIBO(GLuint ibo)
{
	this->ibo = ibo;
}

void Model::setSkeleton(Skeleton* skeleton)
{
	this->skeleton = skeleton;
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

} // namespace Emergent
