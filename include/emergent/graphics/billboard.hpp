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

#ifndef EMERGENT_GRAPHICS_BILLBOARD_HPP
#define EMERGENT_GRAPHICS_BILLBOARD_HPP

#include <emergent/graphics/gl3w.hpp>
#include <emergent/graphics/scene-object.hpp>
#include <emergent/graphics/material.hpp>
#include <emergent/graphics/camera.hpp>
#include <emergent/math/types.hpp>
#include <vector>

namespace Emergent
{

/**
 * Enumerates billboard alignment modes
 *
 * @ingroup graphics
 */
enum class BillboardAlignmentMode
{
	// Aligns to face camera
	SPHERICAL,
	
	// Rotates about local up vector to face camera
	CYLINDRICAL
};

/**
 * A two-dimensional billboard which can rendered in a three-dimensional scene.
 *
 * @ingroup graphics
 */
class Billboard
{
public:
	Billboard();
	
	void setTranslation(const Vector3& translation);
	void setRotation(const glm::quat& rotation);
	void setDimensions(const Vector2& dimensions);
	void setTextureCoordinates(const Vector2& min, const Vector2& max);
	void setTintColor(const Vector4& color);
	
	const Vector3& getTranslation() const;
	const glm::quat& getRotation() const;
	const Vector2& getDimensions() const;
	const Vector2& getTextureCoordinatesMin() const;
	const Vector2& getTextureCoordinatesMax() const;
	const Vector4& getTintColor() const;
	
private:
	Vector3 translation;
	glm::quat rotation;
	Vector2 dimensions;
	Vector2 coordinatesMin;
	Vector2 coordinatesMax;
	Vector4 tintColor;
};

inline void Billboard::setTranslation(const Vector3& translation)
{
	this->translation = translation;
}

inline void Billboard::setRotation(const glm::quat& rotation)
{
	this->rotation = rotation;
}

inline void Billboard::setDimensions(const Vector2& dimensions)
{
	this->dimensions = dimensions;
}

inline void Billboard::setTextureCoordinates(const Vector2& min, const Vector2& max)
{
	this->coordinatesMin = min;
	this->coordinatesMax = max;
}

inline void Billboard::setTintColor(const Vector4& color)
{
	this->tintColor = color;
}

inline const Vector3& Billboard::getTranslation() const
{
	return translation;
}

inline const glm::quat& Billboard::getRotation() const
{
	return rotation;
}

inline const Vector2& Billboard::getDimensions() const
{
	return dimensions;
}

inline const Vector2& Billboard::getTextureCoordinatesMin() const
{
	return coordinatesMin;
}

inline const Vector2& Billboard::getTextureCoordinatesMax() const
{
	return coordinatesMax;
}

inline const Vector4& Billboard::getTintColor() const
{
	return tintColor;
}

/**
 * A batch of billboards which can be rendered in a scene.
 *
 * @ingroup graphics
 */
class BillboardBatch: public SceneObject
{
public:
	/// Specifies a range of billboards within the batch which correspond with a specific material.
	struct Range
	{
		Range();
		
		Material* material;
		std::size_t start;
		std::size_t length;
	};
	
	BillboardBatch();
	virtual ~BillboardBatch();
	
	void setAlignment(const Camera* camera, BillboardAlignmentMode mode);
	void setAlignmentVector(const Vector3& direction);
	
	void resize(std::size_t count);
	
	void update();
	
	/// Returns SceneObjectType::BILLBOARD_BATCH
	virtual SceneObjectType getSceneObjectType() const;
	
	/// Adds a range to the batch. 
	BillboardBatch::Range* addRange();
	
	/// Removes all ranges from the batch.
	void removeRanges();
	
	/// Returns the number of ranges in the batch
	std::size_t getRangeCount() const;
	
	/// Returns the range at the specified index
	const BillboardBatch::Range* getRange(std::size_t index) const;
	
	/// @copydoc BillboardBatch::getRange() const
	BillboardBatch::Range* getRange(std::size_t index);
	
	std::size_t getBillboardCount() const;
	const Billboard* getBillboard(std::size_t index) const;
	Billboard* getBillboard(std::size_t index);
	
	
	std::size_t vertexSize;
	std::size_t vertexCount;
	float* vertexData;
	std::size_t indexCount;
	std::size_t triangleCount;
	GLuint vao;
	GLuint vbo;
	GLuint ibo;
	
private:
	std::vector<Billboard> billboards;
	std::vector<Range> ranges;
	const Camera* camera;
	BillboardAlignmentMode alignmentMode;
	Vector3 alignmentVector;
};

inline SceneObjectType BillboardBatch::getSceneObjectType() const
{
	return SceneObjectType::BILLBOARD_BATCH;
}

inline std::size_t BillboardBatch::getRangeCount() const
{
	return ranges.size();
}

inline const BillboardBatch::Range* BillboardBatch::getRange(std::size_t index) const
{
	return &ranges[index];
}

inline BillboardBatch::Range* BillboardBatch::getRange(std::size_t index)
{
	return &ranges[index];
}

inline std::size_t BillboardBatch::getBillboardCount() const
{
	return billboards.size();
}

inline const Billboard* BillboardBatch::getBillboard(std::size_t index) const
{
	return &billboards[index];
}

inline Billboard* BillboardBatch::getBillboard(std::size_t index)
{
	return &billboards[index];
}

} // namespace Emergent

#endif // EMERGENT_GRAPHICS_BILLBOARD_HPP
