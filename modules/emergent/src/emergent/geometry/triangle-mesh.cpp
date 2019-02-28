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

#include <emergent/geometry/triangle-mesh.hpp>
#include <fstream>
#include <map>
#include <sstream>
#include <limits>

namespace Emergent
{

TriangleMesh::TriangleMesh(const std::vector<Vector3>& vertices, const std::vector<std::size_t>& indices)
{
	if (indices.size() % 3 != 0)
	{
		throw std::runtime_error("TriangleMesh::TriangleMesh(): index count is not a multuple of 3.");
	}
	
	// Copy vertices
	this->vertices.resize(vertices.size());
	for (std::size_t i = 0; i < vertices.size(); ++i)
	{
		TriangleMesh::Vertex* vertex = new TriangleMesh::Vertex();
		vertex->edge = nullptr;
		vertex->position = vertices[i];
		vertex->index = i;
		
		this->vertices[i] = vertex;
	}
	
	// Allocate triangles
	triangles.resize(indices.size() / 3, nullptr);
	std::size_t currentTriangle = 0;
	
	// Load triangles
	std::map<std::pair<std::size_t, std::size_t>, TriangleMesh::Edge*> edgeMap;
	for (std::size_t i = 0; i < indices.size(); i += 3)
	{
		std::size_t a = indices[i];
		std::size_t b = indices[i + 1];
		std::size_t c = indices[i + 2];
		
		if (a >= vertices.size() || b >= vertices.size() || c >= vertices.size())
		{
			throw std::runtime_error("TriangleMesh::TriangleMesh(): Mesh contains invalid index.");
		}
		
		// Allocate three edges and a triangle
		TriangleMesh::Edge* ab = new TriangleMesh::Edge();
		TriangleMesh::Edge* bc = new TriangleMesh::Edge();
		TriangleMesh::Edge* ca = new TriangleMesh::Edge();
		TriangleMesh::Triangle* triangle = new TriangleMesh::Triangle();

		// Set triangle start edge
		triangle->edge = ab;

		// For each edge in this triangle
		std::size_t triangleIndices[] = {a, b, c};
		TriangleMesh::Edge* triangleEdges[] = {ab, bc, ca};
		for (std::size_t j = 0; j < 3; ++j)
		{
			// Set edge properties
			TriangleMesh::Edge* edge = triangleEdges[j];
			edge->triangle = triangle;
			edge->vertex = this->vertices[triangleIndices[j]];
			edge->previous = triangleEdges[(j + 2) % 3];
			edge->next = triangleEdges[(j + 1) % 3];
			edge->symmetric = nullptr;

			// Point vertex to this edge
			edge->vertex->edge = edge;

			// Check for symmetry
			std::pair<std::size_t, std::size_t> symmetricPair(triangleIndices[(j + 1) % 3], triangleIndices[j]);
			std::map<std::pair<std::size_t, std::size_t>, TriangleMesh::Edge*>::iterator it = edgeMap.find(symmetricPair);
			if (it == edgeMap.end())
			{
				// No symmetric edge found, insert this edge into the map
				std::pair<std::size_t, std::size_t> pair(triangleIndices[j], triangleIndices[(j + 1) % 3]);
				edgeMap[pair] = edge;
			}
			else
			{
				// Symmetric edge found, connect
				edge->symmetric = it->second;
				it->second->symmetric = edge;
			}
		}

		// Set edge indices and add edges to the edge list
		ab->index = edges.size();
		edges.push_back(ab);
		bc->index = edges.size();
		edges.push_back(bc);
		ca->index = edges.size();
		edges.push_back(ca);
		
		// Set triangle index and add triangle to the triangle list
		triangle->index = currentTriangle;
		triangles[currentTriangle++] = triangle;
	}
	
	calculateNormals();
}

TriangleMesh::~TriangleMesh()
{
	for (std::size_t i = 0; i < vertices.size(); ++i)
		delete vertices[i];
	for (std::size_t i = 0; i < edges.size(); ++i)
		delete edges[i];
	for (std::size_t i = 0; i < triangles.size(); ++i)
		delete triangles[i];
}

void TriangleMesh::calculateNormals()
{
	for (std::size_t i = 0; i < triangles.size(); ++i)
	{
		TriangleMesh::Triangle* triangle = triangles[i];

		// Calculate surface normal
		const Vector3& a = triangle->edge->vertex->position;
		const Vector3& b = triangle->edge->next->vertex->position;
		const Vector3& c = triangle->edge->previous->vertex->position;
		Vector3 ba = b - a;
		Vector3 ca = c - a;
		triangle->normal = glm::normalize(glm::cross(ba, ca));
	}
}

} // namespace Emergent
