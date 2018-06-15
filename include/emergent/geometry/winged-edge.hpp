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

#ifndef EMERGENT_GEOMETRY_WINGED_EDGE_HPP
#define EMERGENT_GEOMETRY_WINGED_EDGE_HPP

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
class WingedEdge
{
public:
	struct Vertex;
	struct Edge;
	struct Triangle;
	
	/**
	 * Creates an instance of WingedEdge.
	 */
	WingedEdge();
	
	/**
	 * Destroys an instance of WingedEdge.
	 */
	~WingedEdge();
	
	/**
	 * Forms a winged-edge mesh from a list of vertices and indices.
	 *
	 * @param vertices Specifies a list of vertices.
	 * @param indices Specifies a list of indices.
	 * @return `true` if the mesh was successfully created, `false` otherwise.
	 */
	bool create(const std::vector<Vector3>& vertices, const std::vector<std::size_t>& indices);
	
	/**
	 * Destroys the winged-edge mesh.
	 */
	void destroy();
	
	/**
	 * Loads this mesh from a triangulated Wavefront OBJ file. This method only supported **triangulated** Wavefront OBJ files. The supported commands are `v`, `f` and comment lines beginning with `#`.
	 *
	 * @param filename Path to the Wavefront OBJ file.
	 * @return `true` if the winged-edge was successfully loaded from the OBJ file, `false` otherwise.
	 */
	bool loadOBJ(const std::string& filename);
	
	/**
	 * Calculates the faceted surface normals for each triangle.
	 */
	void calculateNormals();
	
	/// Returns a pointer to the winged-edge mesh vertices
	const std::vector<WingedEdge::Vertex*>* getVertices() const;
	
	/// Returns a pointer to the winged-edge mesh edges
	const std::vector<WingedEdge::Edge*>* getEdges() const;
	
	/// Returns a pointer to the winged-edge mesh triangles
	const std::vector<WingedEdge::Triangle*>* getTriangles() const;
	
	/// @copydoc WingedEdge::getVertices() const
	std::vector<WingedEdge::Vertex*>* getVertices();
	
	/// @copydoc WingedEdge::getEdges() const
	std::vector<WingedEdge::Edge*>* getEdges();
	
	/// @copydoc WingedEdge::getTriangles() const
	std::vector<WingedEdge::Triangle*>* getTriangles();
	
	/**
	 * Winged-edge vertex which contains a pointer to its parent edge, a position vector, and an index.
	 */
	struct Vertex
	{
		/// Pointer to the edge to which this vertex belongs
		WingedEdge::Edge* edge;
		
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
		WingedEdge::Vertex* vertex;     
		
		/// Pointer to the triangle to which this edge belongs
		WingedEdge::Triangle* triangle;
		
		/// Pointer to the previous edge in the parent triangle
		WingedEdge::Edge* previous;
		
		/// Pointer to the next edge in the parent triangle
		WingedEdge::Edge* next;
		
		/// Pointer to the symmetric edge
		WingedEdge::Edge* symmetric;
		
		/// Index of this edge
		std::size_t index;
	};
	
	/**
	 * Winged-edge triangle which contains a pointer to its first edge and its normal vector.
	 */
	struct Triangle
	{
		/// Pointer to the first edge in this triangle
		WingedEdge::Edge* edge;
		
		/// Faceted surface normal
		Vector3 normal;
		
		/// Index of this triangle
		std::size_t index;
	};
	
private:	
	/**
	 * Reads Wavefront OBJ data from an input stream
	 *
	 * @param stream Input stream containing OBJ data
	 * @param filename Path to the OBJ file
	 * @return `true` if OBJ data was successfully read from the file.
	 */
	bool readOBJ(std::istream* stream, const std::string& filename);
	
	std::vector<WingedEdge::Vertex*> vertices;
	std::vector<WingedEdge::Edge*> edges;
	std::vector<WingedEdge::Triangle*> triangles;
};

inline const std::vector<WingedEdge::Vertex*>* WingedEdge::getVertices() const
{
	return &vertices;
}

inline const std::vector<WingedEdge::Edge*>* WingedEdge::getEdges() const
{
	return &edges;
}

inline const std::vector<WingedEdge::Triangle*>* WingedEdge::getTriangles() const
{
	return &triangles;
}

inline std::vector<WingedEdge::Vertex*>* WingedEdge::getVertices()
{
	return &vertices;
}

inline std::vector<WingedEdge::Edge*>* WingedEdge::getEdges()
{
	return &edges;
}

inline std::vector<WingedEdge::Triangle*>* WingedEdge::getTriangles()
{
	return &triangles;
}

} // namespace Emergent

#endif // EMERGENT_GEOMETRY_WINGED_EDGE_HPP
