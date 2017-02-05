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
	ConvexHull(6)
{}

ViewFrustum::ViewFrustum(const Matrix4& m):
	ConvexHull(6)
{
	setMatrix(m);
}

void ViewFrustum::setMatrix(const Matrix4& m)
{
	this->matrix = m;
	calculatePlanes();
	calculateCorners();
}

void ViewFrustum::calculatePlanes()
{
	Matrix4 transpose = glm::transpose(matrix);
	ConvexHull::setPlane(0, Plane(transpose[3] + transpose[0]));
	ConvexHull::setPlane(1, Plane(transpose[3] - transpose[0]));
	ConvexHull::setPlane(2, Plane(transpose[3] + transpose[1]));
	ConvexHull::setPlane(3, Plane(transpose[3] - transpose[1]));
	ConvexHull::setPlane(4, Plane(transpose[3] + transpose[2]));
	ConvexHull::setPlane(5, Plane(transpose[3] - transpose[2]));
}

void ViewFrustum::calculateCorners()
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
