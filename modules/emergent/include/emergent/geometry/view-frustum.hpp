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
	/**
	 * Creates an instance of ViewFrustum.
	 */
	ViewFrustum();

	ViewFrustum(const ViewFrustum& viewFrustum);
	ViewFrustum& operator=(const ViewFrustum& viewFrustum);
	
	/**
	 * Sets the view matrix of the frustum.
	 *
	 * @param view Camera view matrix.
	 */
	void setViewMatrix(const Matrix4& view);
	
	/**
	 * Sets the projection matrix of the frustum.
	 *
	 * @param projection Camera projection matrix.
	 */
	void setProjectionMatrix(const Matrix4& projection);
	
	/**
	 * Sets the view and projection matrices of the frustum.
	 *
	 * @param view Camera view matrix.
	 * @param projection Camera projection matrix.
	 */
	void setMatrices(const Matrix4& view, const Matrix4& projection);
	
	/**
	 * Returns the frustum view matrix.
	 */
	const Matrix4& getViewMatrix() const;
	
	/**
	 * Returns the frustum projection matrix.
	 */
	const Matrix4& getProjectionMatrix() const;
	
	/**
	 * Returns the frustum view-projection matrix.
	 */
	const Matrix4& getViewProjectionMatrix() const;
	
	/**
	 * Returns the left plane of the frustum.
	 */
	const Plane& getLeft() const;
	
	/**
	 * Returns the right plane of the frustum.
	 */
	const Plane& getRight() const;
	
	/**
	 * Returns the bottom plane of the frustum.
	 */
	const Plane& getBottom() const;
	
	/**
	 * Returns the top plane of the frustum.
	 */
	const Plane& getTop() const;
	
	/**
	 * Returns the near plane of the frustum.
	 */
	const Plane& getNear() const;
	
	/**
	 * Returns the far plane of the frustum.
	 */
	const Plane& getFar() const;
	
	/**
	 * Returns the number of corners (8) in the frustum.
	 */
	std::size_t getCornerCount() const;
	
	/**
	 * Returns the frustum corner at the specified index. The corners are stored in the following order: `ntl`, `ntr`, `nbl`, `nbr`, `ftl`, `ftr`, `fbl`, `fbr`. The corners are referred to by the three intersecting planes at which they are located. Where `n` is near, `f` is far, `t` is top, `b` is bottom, `l` is left, and `r` is right. So `ntl` refers to the corner at the intersection of the near, top, and left planes.
	 *
	 * @param index Index of a corner.
	 */
	const Vector3& getCorner(std::size_t index) const;

	/// Compares two view frustums for equality.
	bool operator==(const ViewFrustum& rhs) const;
	
protected:
	virtual void recalculateFrustum();
	
private:
	void recalculatePlanes();
	void recalculateCorners();	
	
	Matrix4 view;
	Matrix4 projection;
	Matrix4 viewProjection;
	Vector3 corners[8];
};

inline const Matrix4& ViewFrustum::getViewMatrix() const
{
	return view;
}

inline const Matrix4& ViewFrustum::getProjectionMatrix() const
{
	return projection;
}

inline const Matrix4& ViewFrustum::getViewProjectionMatrix() const
{
	return viewProjection;
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

inline const Vector3& ViewFrustum::getCorner(std::size_t index) const
{
	return corners[index];
}

inline bool ViewFrustum::operator==(const ViewFrustum& rhs) const
{
	return (view == rhs.view && projection == rhs.projection);
}

} // namespace Emergent

#endif // EMERGENT_GEOMETRY_VIEW_FRUSTUM_HPP
