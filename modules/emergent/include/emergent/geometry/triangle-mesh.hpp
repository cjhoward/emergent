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

#ifndef EMERGENT_GEOMETRY_TRIANGLE_MESH_HPP
#define EMERGENT_GEOMETRY_TRIANGLE_MESH_HPP

#include <emergent/math/types.hpp>
#include <iostream>
#include <string>
#include <vector>

namespace Emergent
{

/**
 * Winged-edge triangle mesh.
 *
 * @ingroup geometry
 */
class TriangleMesh
{
public:
	struct Vertex;
	struct Edge;
	struct Triangle;

	/**
	 * Creates a triangle mesh from a list of vertices and indices.
	 *
	 * @param vertices Specifies a list of vertices.
	 * @param indices Specifies a list of indices.
	 * @return `true` if the mesh was successfully created, `false` otherwise.
	 */
	TriangleMesh(const std::vector<Vector3>& vertices, const std::vector<std::size_t>& indices);
	
	/**
	 * Destroys a triangle mesh.
	 */
	~TriangleMesh();
		
	/// Returns a pointer to the triangle mesh vertices
	const std::vector<TriangleMesh::Vertex*>* getVertices() const;
	
	/// Returns a pointer to the triangle mesh edges
	const std::vector<TriangleMesh::Edge*>* getEdges() const;
	
	/// Returns a pointer to the triangle mesh triangles
	const std::vector<TriangleMesh::Triangle*>* getTriangles() const;
	
	/// @copydoc TriangleMesh::getVertices() const
	std::vector<TriangleMesh::Vertex*>* getVertices();
	
	/// @copydoc TriangleMesh::getEdges() const
	std::vector<TriangleMesh::Edge*>* getEdges();
	
	/// @copydoc TriangleMesh::getTriangles() const
	std::vector<TriangleMesh::Triangle*>* getTriangles();
	
	/**
	 * Winged-edge vertex which contains a pointer to its parent edge, a position vector, and an index.
	 */
	struct Vertex
	{
		/// Pointer to the edge to which this vertex belongs
		TriangleMesh::Edge* edge;
		
		/// Vertex position vector
		Vector3 position;
		
		/// Index of this vertex
		std::size_t index;
	};
	
	/**
	 * Winged-edge edge which contains pointers to its starting vertex, parent triangle, and related edges.
	 */
	struct Edge
	{
		/// Pointer to the vertex at which the edge starts
		TriangleMesh::Vertex* vertex;     
		
		/// Pointer to the triangle to which this edge belongs
		TriangleMesh::Triangle* triangle;
		
		/// Pointer to the previous edge in the parent triangle
		TriangleMesh::Edge* previous;
		
		/// Pointer to the next edge in the parent triangle
		TriangleMesh::Edge* next;
		
		/// Pointer to the symmetric edge
		TriangleMesh::Edge* symmetric;
		
		/// Index of this edge
		std::size_t index;
	};
	
	/**
	 * Winged-edge triangle which contains a pointer to its first edge and its normal vector.
	 */
	struct Triangle
	{
		/// Pointer to the first edge in this triangle
		TriangleMesh::Edge* edge;
		
		/// Faceted surface normal
		Vector3 normal;
		
		/// Index of this triangle
		std::size_t index;
	};
	
private:	
	/**
	 * Calculates the faceted surface normals for each triangle.
	 */
	void calculateNormals();
	
	std::vector<TriangleMesh::Vertex*> vertices;
	std::vector<TriangleMesh::Edge*> edges;
	std::vector<TriangleMesh::Triangle*> triangles;
};

inline const std::vector<TriangleMesh::Vertex*>* TriangleMesh::getVertices() const
{
	return &vertices;
}

inline const std::vector<TriangleMesh::Edge*>* TriangleMesh::getEdges() const
{
	return &edges;
}

inline const std::vector<TriangleMesh::Triangle*>* TriangleMesh::getTriangles() const
{
	return &triangles;
}

inline std::vector<TriangleMesh::Vertex*>* TriangleMesh::getVertices()
{
	return &vertices;
}

inline std::vector<TriangleMesh::Edge*>* TriangleMesh::getEdges()
{
	return &edges;
}

inline std::vector<TriangleMesh::Triangle*>* TriangleMesh::getTriangles()
{
	return &triangles;
}

} // namespace Emergent

#endif // EMERGENT_GEOMETRY_TRIANGLE_MESH_HPP
