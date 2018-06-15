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

#ifndef EMERGENT_GRAPHICS_MODEL_HPP
#define EMERGENT_GRAPHICS_MODEL_HPP

#include <emergent/graphics/gl3w.hpp>
#include <emergent/graphics/vertex-format.hpp>
#include <emergent/geometry/aabb.hpp>
#include <string>
#include <vector>
#include <map>

namespace Emergent
{

class Material;
class Skeleton;
class ModelInstance;
class WingedEdge;

/**
 * A 3D model.
 *
 * @ingroup graphics
 */
class Model
{
public:
	/**
	 * A model group encapsulates the geometry of a model which corresponds to a specific material.
	 */
	struct Group
	{
		/// Name of the model group
		std::string name;
		
		/// Pointer to the material with which this group is associated.
		Material* material;
		
		/// Offset to the index of the first triangle in this group
		std::uint32_t indexOffset;
		
		/// Number of triangles in this group.
		std::uint32_t triangleCount;
		
		/// AABB which contains all geometry in this group.
		AABB bounds;
	};
	
	/**
	 * Creates an instance of Model.
	 */
	Model();
	
	/**
	 * Destroys an instance of Model.
	 */
	~Model();
	
	/**
	 * Frees model data.
	 */
	void destroy();
	
	/**
	 * Creates a model from a winged-edge mesh.
	 *
	 * @param mesh Specifies the winged-edge mesh from which to create a model.
	 * @return `true` if the model was sucessfully created, `false` otherwise.
	 */
	bool create(const WingedEdge* mesh);
	
	/**
	 * Creates a model instance of this model.
	 *
	 * @return Pointer to the new instance of this model.
	 */
	ModelInstance* createInstance() const;
	
	/**
	 * Adds a model group to this model. The added group becomes owned by this model and will be deleted when Model::destroy() is called.
	 *
	 * @param group Specifies the model group to add.
	 */
	void addGroup(Model::Group* group);
	
	/// Sets the vertex format flags.
	void setVertexFormat(std::uint32_t vertexFormat);
	
	/// Sets the VAO
	void setVAO(GLuint vao);
	
	/// Sets the VBO
	void setVBO(GLuint vbo);
	
	/// Sets the IBO
	void setIBO(GLuint ibo);
	
	/// Sets the skeleton. The set skeleton becomes owned by this model and will be deleted when Model::destroy() is called.
	void setSkeleton(Skeleton* skeleton);
	
	/**
	 * Sets the bounds of this model.
	 *
	 * @param bounds Specifies the model bounds.
	 */
	void setBounds(const AABB& bounds);
	
	/// Returns the number of model groups in this model.
	std::size_t getGroupCount() const;
	
	/// Returns the model group at the specified index.
	const Model::Group* getGroup(std::size_t index) const;
	
	/// @copydoc Model::getGroup(std::size_t) const
	Model::Group* getGroup(std::size_t index);
	
	/// Returns the model group with the specified name, or `nullptr` if it does not exist.
	const Model::Group* getGroup(const std::string& name) const;
	
	/// @copydoc Model::getGroup(const std::string&) const
	Model::Group* getGroup(const std::string& name);
	
	/// Returns the vertex format flags
	std::uint32_t getVertexFormat();
	
	/// Returns the VAO
	GLuint getVAO() const;
	
	/// Returns the VBO
	GLuint getVBO() const;
	
	/// Returns the IBO
	GLuint getIBO() const;
	
	/// Returns the skeleton
	const Skeleton* getSkeleton() const;
	
	/// @copydoc Model::getSkeleton() const
	Skeleton* getSkeleton();
	
	/// Returns the bounds of this model.
	const AABB& getBounds() const;
	
private:
	/// Generates vertex data from a winged-edge mesh
	static float* generateVertexData(const WingedEdge* mesh);
	
	/// Generates index data from a winged-edge mesh
	static std::uint32_t* generateIndexData(const WingedEdge* mesh);
	
	/**
	 * Reads Emergent MDL data from an input stream.
	 *
	 * @param stream Input stream containing MDL data
	 * @param filename Path to the MDL file
	 * @return `true` if MDL data was successfully read from the file.
	 */
	bool readMDL(std::istream* stream, const std::string& filename);
	
	std::vector<Model::Group*> groups;
	std::map<std::string, Model::Group*> groupMap;
	std::uint32_t vertexFormat;
	GLuint vao;
	GLuint vbo;
	GLuint ibo;
	Skeleton* skeleton;
	AABB bounds;
};

inline std::size_t Model::getGroupCount() const
{
	return groups.size();
}

inline const Model::Group* Model::getGroup(std::size_t index) const
{
	return groups[index];
}

inline Model::Group* Model::getGroup(std::size_t index)
{
	return groups[index];
}

inline std::uint32_t Model::getVertexFormat()
{
	return vertexFormat;
}

inline GLuint Model::getVAO() const
{
	return vao;
}

inline GLuint Model::getVBO() const
{
	return vbo;
}

inline GLuint Model::getIBO() const
{
	return ibo;
}

inline const Skeleton* Model::getSkeleton() const
{
	return skeleton;
}
	
inline Skeleton* Model::getSkeleton()
{
	return skeleton;
}

inline const AABB& Model::getBounds() const
{
	return bounds;
}

} // namespace Emergent

#endif // EMERGENT_GRAPHICS_MODEL_HPP
