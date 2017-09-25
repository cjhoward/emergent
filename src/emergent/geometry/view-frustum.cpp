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

#include <emergent/geometry/view-frustum.hpp>

namespace Emergent
{

ViewFrustum::ViewFrustum():
	ConvexHull(6),
	view(1.0f),
	projection(1.0f),
	viewProjection(1.0f)
{
	recalculatePlanes();
	recalculateCorners();
}

void ViewFrustum::setViewMatrix(const Matrix4& view)
{
	this->view = view;
	recalculateFrustum();
}

void ViewFrustum::setProjectionMatrix(const Matrix4& projection)
{
	this->projection = projection;
	recalculateFrustum();
}

void ViewFrustum::setMatrices(const Matrix4& view, const Matrix4& projection)
{
	this->view = view;
	this->projection = projection;
	recalculateFrustum();
}

void ViewFrustum::recalculateFrustum()
{
	viewProjection = projection * view;
	recalculatePlanes();
	recalculateCorners();
}

void ViewFrustum::recalculatePlanes()
{
	Matrix4 transpose = glm::transpose(viewProjection);
	ConvexHull::setPlane(0, Plane(transpose[3] + transpose[0]));
	ConvexHull::setPlane(1, Plane(transpose[3] - transpose[0]));
	ConvexHull::setPlane(2, Plane(transpose[3] + transpose[1]));
	ConvexHull::setPlane(3, Plane(transpose[3] - transpose[1]));
	ConvexHull::setPlane(4, Plane(transpose[3] + transpose[2]));
	ConvexHull::setPlane(5, Plane(transpose[3] - transpose[2]));
}

void ViewFrustum::recalculateCorners()
{
	corners[0] = Plane::intersection(getNear(), getTop(), getLeft());
	corners[1] = Plane::intersection(getNear(), getTop(), getRight());
	corners[2] = Plane::intersection(getNear(), getBottom(), getLeft());
	corners[3] = Plane::intersection(getNear(), getBottom(), getRight());
	corners[4] = Plane::intersection(getFar(), getTop(), getLeft());
	corners[5] = Plane::intersection(getFar(), getTop(), getRight());
	corners[6] = Plane::intersection(getFar(), getBottom(), getLeft());
	corners[7] = Plane::intersection(getFar(), getBottom(), getRight());
}

} // namespace Emergent
