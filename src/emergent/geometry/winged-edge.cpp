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

#include <emergent/geometry/winged-edge.hpp>
#include <fstream>
#include <map>
#include <sstream>
#include <limits>

namespace Emergent
{

WingedEdge::WingedEdge()
{}

WingedEdge::~WingedEdge()
{
	destroy();
}

bool WingedEdge::create(const std::vector<Vector3>& vertices, const std::vector<std::size_t>& indices)
{
	destroy();
	
	if (indices.size() % 3 != 0)
	{
		std::cerr << "WingedEdge::create(): index count is non power of 3\n";
		return false;
	}
	
	// Copy vertices
	this->vertices.resize(vertices.size());
	for (std::size_t i = 0; i < vertices.size(); ++i)
	{
		WingedEdge::Vertex* vertex = new WingedEdge::Vertex();
		vertex->edge = nullptr;
		vertex->position = vertices[i];
		vertex->index = i;
		
		this->vertices[i] = vertex;
	}
	
	// Allocate triangles
	triangles.resize(indices.size() / 3, nullptr);
	std::size_t currentTriangle = 0;
	
	// Load triangles
	std::map<std::pair<std::size_t, std::size_t>, WingedEdge::Edge*> edgeMap;
	for (std::size_t i = 0; i < indices.size(); i += 3)
	{
		std::size_t a = indices[i];
		std::size_t b = indices[i + 1];
		std::size_t c = indices[i + 2];
		
		if (a >= vertices.size() || b >= vertices.size() || c >= vertices.size())
		{
			std::cerr << "WingedEdge::create(): Mesh contains invalid index.\n";
			destroy();
			return false;
		}
		
		// Allocate three edges and a triangle
		WingedEdge::Edge* ab = new WingedEdge::Edge();
		WingedEdge::Edge* bc = new WingedEdge::Edge();
		WingedEdge::Edge* ca = new WingedEdge::Edge();
		WingedEdge::Triangle* triangle = new WingedEdge::Triangle();

		// Set triangle start edge
		triangle->edge = ab;

		// For each edge in this triangle
		std::size_t triangleIndices[] = {a, b, c};
		WingedEdge::Edge* triangleEdges[] = {ab, bc, ca};
		for (std::size_t j = 0; j < 3; ++j)
		{
			// Set edge properties
			WingedEdge::Edge* edge = triangleEdges[j];
			edge->triangle = triangle;
			edge->vertex = this->vertices[triangleIndices[j]];
			edge->previous = triangleEdges[(j + 2) % 3];
			edge->next = triangleEdges[(j + 1) % 3];
			edge->symmetric = nullptr;

			// Point vertex to this edge
			edge->vertex->edge = edge;

			// Check for symmetry
			std::pair<std::size_t, std::size_t> symmetricPair(triangleIndices[(j + 1) % 3], triangleIndices[j]);
			std::map<std::pair<std::size_t, std::size_t>, WingedEdge::Edge*>::iterator it = edgeMap.find(symmetricPair);
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

		// Add edges and triangle to lists
		edges.push_back(ab);
		edges.push_back(bc);
		edges.push_back(ca);
		triangles[currentTriangle++] = triangle;
	}
	
	calculateNormals();
	
	return true;
}

void WingedEdge::destroy()
{
	for (std::size_t i = 0; i < vertices.size(); ++i)
		delete vertices[i];
	for (std::size_t i = 0; i < edges.size(); ++i)
		delete edges[i];
	for (std::size_t i = 0; i < triangles.size(); ++i)
		delete triangles[i];
	
	vertices.clear();
	edges.clear();
	triangles.clear();
}

bool WingedEdge::loadOBJ(const std::string& filename)
{
	// Open OBJ file
	std::ifstream file(filename.c_str());
	if (!file.is_open())
	{
		std::cerr << "WingedEdge::loadOBJ(): Failed to open Wavefront OBJ file \"" << filename << "\"" << std::endl;
		return false;
	}

	// Read OBJ file from file stream
	if (!readOBJ(&file, filename))
	{
		std::cerr << "WingedEdge::loadOBJ(): Failed to read Wavefront OBJ file \"" << filename << "\"" << std::endl;
		file.close();
		return false;
	}

	// Close OBJ file
	file.close();

	return true;
}

void WingedEdge::calculateNormals()
{
	for (std::size_t i = 0; i < triangles.size(); ++i)
	{
		WingedEdge::Triangle* triangle = triangles[i];

		// Calculate surface normal
		const Vector3& a = triangle->edge->vertex->position;
		const Vector3& b = triangle->edge->next->vertex->position;
		const Vector3& c = triangle->edge->previous->vertex->position;
		Vector3 ba = b - a;
		Vector3 ca = c - a;
		triangle->normal = glm::normalize(glm::cross(ba, ca));
	}
}

bool WingedEdge::readOBJ(std::istream* stream, const std::string& filename)
{
	std::string line;
	std::vector<Vector3> vertices;
	std::vector<std::size_t> indices;

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
		
		if (tokens[0] == "v")
		{
			if (tokens.size() != 4)
			{
				std::cerr << "WingedEdge::readOBJ(): Invalid line \"" << line << "\" in file \"" << filename << "\"" << std::endl;
				return false;
			}
			
			Vector3 vertex;
			
			std::stringstream(tokens[1]) >> vertex.x;
			std::stringstream(tokens[2]) >> vertex.y;
			std::stringstream(tokens[3]) >> vertex.z;

			vertices.push_back(vertex);
		}
		else if (tokens[0] == "f")
		{
			if (tokens.size() != 4)
			{
				std::cerr << "WingedEdge::readOBJ(): Invalid line \"" << line << "\" in file \"" << filename << "\"" << std::endl;
				return false;
			}
			
			std::size_t a, b, c;
			std::stringstream(tokens[1]) >> a;
			std::stringstream(tokens[2]) >> b;
			std::stringstream(tokens[3]) >> c;
			
			a -= 1;
			b -= 1;
			c -= 1;
			
			indices.push_back(a);
			indices.push_back(b);
			indices.push_back(c);
		}
	}
	
	return create(vertices, indices);
}

} // namespace Emergent
