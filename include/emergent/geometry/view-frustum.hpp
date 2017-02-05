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

#ifndef EMERGENT_GEOMETRY_VIEW_FRUSTUM_HPP
#define EMERGENT_GEOMETRY_VIEW_FRUSTUM_HPP

#include <emergent/geometry/convex-hull.hpp>
#include <emergent/math/types.hpp>

namespace Emergent
{

/**
 * A camera's view frustum.
 *
 * @ingroup geometry
 */
class ViewFrustum: public ConvexHull
{
public:
	ViewFrustum();
	explicit ViewFrustum(const Matrix4& m);
	
	void setMatrix(const Matrix4& m);
	
	const Matrix4& getMatrix() const;
	const Plane& getLeft() const;
	const Plane& getRight() const;
	const Plane& getBottom() const;
	const Plane& getTop() const;
	const Plane& getNear() const;
	const Plane& getFar() const;
	
	std::size_t getCornerCount() const;
	const glm::vec3& getCorner(std::size_t index) const;

private:
	void calculatePlanes();
	void calculateCorners();	
	
	Matrix4 matrix;
	glm::vec3 corners[8];
};

inline const Matrix4& ViewFrustum::getMatrix() const
{
	return matrix;
}

inline const Plane& ViewFrustum::getLeft() const
{
	return ConvexHull::getPlane(0);
}

inline const Plane& ViewFrustum::getRight() const
{
	return ConvexHull::getPlane(1);
}

inline const Plane& ViewFrustum::getBottom() const
{
	return ConvexHull::getPlane(2);
}

inline const Plane& ViewFrustum::getTop() const
{
	return ConvexHull::getPlane(3);
}

inline const Plane& ViewFrustum::getNear() const
{
	return ConvexHull::getPlane(4);
}

inline const Plane& ViewFrustum::getFar() const
{
	return ConvexHull::getPlane(5);
}

inline std::size_t ViewFrustum::getCornerCount() const
{
	return 8;
}

inline const glm::vec3& ViewFrustum::getCorner(std::size_t index) const
{
	return corners[index];
}

} // namespace Emergent

#endif // EMERGENT_GEOMETRY_VIEW_FRUSTUM_HPP

