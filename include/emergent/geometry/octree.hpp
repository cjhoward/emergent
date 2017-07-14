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

#ifndef EMERGENT_GEOMETRY_OCTREE_HPP
#define EMERGENT_GEOMETRY_OCTREE_HPP

#include <cstdlib>
#include <list>
#include <utility>

#include <emergent/math/types.hpp>
#include <emergent/geometry/aabb.hpp>
#include <emergent/geometry/bounding-volume.hpp>
#include <emergent/geometry/ray.hpp>

namespace Emergent
{

/**
 * An octree.
 *
 * Total number of nodes in the octree can be calculated by `(((2^maxDepth)^3) - 1) / 7`.
 *
 * @tparam T Specifies the entry type.
 *
 * @ingroup geometry
 */
template <typename T>
class Octree
{
public:
	/// Specifies the entry type.
	typedef T EntryType;

	/**
	 * Creates an instance of Octree.
	 *
	 * @param maxDepth Specifies the maximum depth of the octree.
	 * @param bounds Specifies the bounds of the octree.
	 */
	Octree(std::size_t maxDepth, const AABB& bounds);
	
	/**
	 * Creates an instance of Octree.
	 *
	 * @param maxDepth Specifies the maximum depth of the octree.
	 */
	explicit Octree(std::size_t maxDepth);

	/**
	 * Destroys an instance of Octree.
	 */
	~Octree();
	
	/**
	 * Resizes the octree.
	 *
	 * @param bounds New bounds of the octree.
	 */
	void resize(const AABB& bounds);

	/**
	 * Inserts an entry into the octree.
	 *
	 * @param volume Specifies the bounding volume of the entry.
	 * @param entry Specifeis the entry data.
	 * @return `true` if the entry was successfully inserted, `false` if the entry volume could not be contained by this octree.
	 */
	bool insert(const AABB& volume, const EntryType& entry);

	/**
	 * Removes all entries from this octree.
	 */
	void clear();

	/**
	 * Queries the octree for a list of entries within the specified volume.
	 *
	 * @param volume Specifies the volume to query.
	 * @return List of entries intersected by the specified volume.
	 */
	std::list<EntryType> query(const BoundingVolume& volume) const;

	/**
	 * Queries the octree for a list of entries within the specified volume.
	 *
	 * @param volume Specifies the volume to query.
	 * @param[out] results Returns a list of entries intersected by the specified volume.
	 */
	void query(const BoundingVolume& volume, std::list<EntryType>* results) const;
	
	/**
	 * Queries the octree for a list of entries whose bounding volumes are intersected by the specified ray.
	 *
	 * @param volume Specifies the ray to query.
	 * @return List of entries intersected by the specified ray.
	 */
	std::list<EntryType> query(const Ray& ray) const;
	
	/**
	 * Queries the octree for a list of entries whose bounding volumes are intersected by the specified ray.
	 *
	 * @param ray Specifies the ray to query.
	 * @param[out] results Returns a list of entries intersected by the specified ray.
	 */
	void query(const Ray& ray, std::list<EntryType>* results) const;

	/**
	 * Returns the bounds of this octree.
	 */
	const AABB& getBounds() const;

	/**
	 * Returns the depth of this octree.
	 */
	std::size_t getDepth() const;

	/**
	 * Returns the maximum depth of this octree.
	 */
	std::size_t getMaxDepth() const;

	/**
	 * Returns a pointer to the specified octant.
	 *
	 * @param index Specifies the index of an octant.
	 */
	const Octree* getOctant(std::size_t index) const;

	/// @copydoc Octree::getOctant(std::size_t) const
	Octree* getOctant(std::size_t index);
	
private:
	/**
	 * Creates an instance of Octree.
	 *
	 * @param bounds Specifies the bounds of this octree.
	 * @param depth Specifies the depth of this octree.
	 * @param maxDepth Specifies the max depth of the root octree.
	 */
	Octree(std::size_t depth, std::size_t maxDepth, const AABB& bounds);
	
	std::size_t depth;
	std::size_t maxDepth;
	AABB bounds;
	Octree* octants[8];
	std::list<std::pair<AABB, EntryType>> entries;
};

template <typename T>
Octree<T>::Octree(std::size_t maxDepth, const AABB& bounds):
	Octree(0, maxDepth, bounds)
{}

template <typename T>
Octree<T>::Octree(std::size_t maxDepth):
	Octree(AABB(Vector3(0.0f), Vector3(0.0f)), 0, maxDepth)
{}

template <typename T>
Octree<T>::Octree(std::size_t depth, std::size_t maxDepth, const AABB& bounds):
	depth(depth),
	maxDepth(maxDepth),
	bounds(bounds)
{
	octants[0] = nullptr;
	octants[1] = nullptr;
	octants[2] = nullptr;
	octants[3] = nullptr;
	octants[4] = nullptr;
	octants[5] = nullptr;
	octants[6] = nullptr;
	octants[7] = nullptr;

	if (depth < maxDepth)
	{
		const Vector3& min = bounds.getMin();
		const Vector3& max = bounds.getMax();
		const Vector3 center = (min + max) * float(0.5);

		const AABB octantBounds[8] =
		{
			AABB(min, center),
			AABB({center.x, min.y, min.z}, {max.x, center.y, center.z}),
			AABB({min.x, min.y, center.z}, {center.x, center.y, max.z}),
			AABB({center.x, min.y, center.z}, {max.x, center.y, max.z}),
			AABB({min.x, center.y, min.z}, {center.x, max.y, center.z}),
			AABB({center.x, center.y, min.z}, {max.x, max.y, center.z}),
			AABB({min.x, center.y, center.z}, {center.x, max.y, max.z}),
			AABB(center, max)
		};

		std::size_t octantDepth = depth + 1;

		octants[0] = new Octree(octantDepth, maxDepth, octantBounds[0]);
		octants[1] = new Octree(octantDepth, maxDepth, octantBounds[1]);
		octants[2] = new Octree(octantDepth, maxDepth, octantBounds[2]);
		octants[3] = new Octree(octantDepth, maxDepth, octantBounds[3]);
		octants[4] = new Octree(octantDepth, maxDepth, octantBounds[4]);
		octants[5] = new Octree(octantDepth, maxDepth, octantBounds[5]);
		octants[6] = new Octree(octantDepth, maxDepth, octantBounds[6]);
		octants[7] = new Octree(octantDepth, maxDepth, octantBounds[7]);
	}
}

template <typename T>
void Octree<T>::resize(const AABB& bounds)
{
	this->bounds = bounds;
	
	if (depth < maxDepth)
	{
		const Vector3& min = bounds.getMin();
		const Vector3& max = bounds.getMax();
		const Vector3 center = (min + max) * float(0.5);

		const AABB octantBounds[8] =
		{
			AABB(min, center),
			AABB({center.x, min.y, min.z}, {max.x, center.y, center.z}),
			AABB({min.x, min.y, center.z}, {center.x, center.y, max.z}),
			AABB({center.x, min.y, center.z}, {max.x, center.y, max.z}),
			AABB({min.x, center.y, min.z}, {center.x, max.y, center.z}),
			AABB({center.x, center.y, min.z}, {max.x, max.y, center.z}),
			AABB({min.x, center.y, center.z}, {center.x, max.y, max.z}),
			AABB(center, max)
		};
		
		octants[0]->resize(octantBounds[0]);
		octants[1]->resize(octantBounds[1]);
		octants[2]->resize(octantBounds[2]);
		octants[3]->resize(octantBounds[3]);
		octants[4]->resize(octantBounds[4]);
		octants[5]->resize(octantBounds[5]);
		octants[6]->resize(octantBounds[6]);
		octants[7]->resize(octantBounds[7]);
	}
}

template <typename T>
Octree<T>::~Octree()
{
	delete octants[0];
	delete octants[1];
	delete octants[2];
	delete octants[3];
	delete octants[4];
	delete octants[5];
	delete octants[6];
	delete octants[7];
}

template <typename T>
bool Octree<T>::insert(const AABB& volume, const EntryType& entry)
{
	// Check if the volume can be contained within this octree
	if (!bounds.contains(volume))
	{
		return false;
	}

	if (depth < maxDepth)
	{
		// Check if the volume can be contained within an octant
		if (octants[0]->insert(volume, entry))
			return true;
		if (octants[1]->insert(volume, entry))
			return true;
		if (octants[2]->insert(volume, entry))
			return true;
		if (octants[3]->insert(volume, entry))
			return true;
		if (octants[4]->insert(volume, entry))
			return true;
		if (octants[5]->insert(volume, entry))
			return true;
		if (octants[6]->insert(volume, entry))
			return true;
		if (octants[7]->insert(volume, entry))
			return true;
	}

	// Volume could not be contained by octants, add entry to this quadtree
	entries.push_back(std::make_pair(volume, entry));

	return true;
}

template <typename T>
void Octree<T>::clear()
{
	entries.clear();

	if (depth < maxDepth)
	{
		octants[0]->clear();
		octants[1]->clear();
		octants[2]->clear();
		octants[3]->clear();
		octants[4]->clear();
		octants[5]->clear();
		octants[6]->clear();
		octants[7]->clear();
	}
}

template <typename T>
std::list<typename Octree<T>::EntryType> Octree<T>::query(const BoundingVolume& volume) const
{
	std::list<EntryType> results;

	query(volume, &results);

	return results;
}

template <typename T>
void Octree<T>::query(const BoundingVolume& volume, std::list<EntryType>* results) const
{
	// Check if the volume intersects with this quadtree
	if (!volume.intersects(bounds))
		return;

	// Perform intersection tests for individual entries
	for (auto it = entries.begin(); it != entries.end(); ++it)
	{
		if (volume.intersects(it->first))
		{
			results->push_back(it->second);
		}
	}

	if (depth < maxDepth)
	{
		// Query octants
		octants[0]->query(volume, results);
		octants[1]->query(volume, results);
		octants[2]->query(volume, results);
		octants[3]->query(volume, results);
		octants[4]->query(volume, results);
		octants[5]->query(volume, results);
		octants[6]->query(volume, results);
		octants[7]->query(volume, results);
	}
}

template <typename T>
std::list<typename Octree<T>::EntryType> Octree<T>::query(const Ray& ray) const
{
	std::list<EntryType> results;

	query(ray, &results);

	return results;
}

template <typename T>
void Octree<T>::query(const Ray& ray, std::list<EntryType>* results) const
{
	// Check if the ray intersects with this quadtree
	if (!std::get<0>(ray.intersects(bounds)))
		return;

	// Perform intersection tests for individual entries
	for (auto it = entries.begin(); it != entries.end(); ++it)
	{
		if (std::get<0>(ray.intersects(it->first)))
		{
			results->push_back(it->second);
		}
	}
	
	if (depth < maxDepth)
	{
		// Query octants
		octants[0]->query(ray, results);
		octants[1]->query(ray, results);
		octants[2]->query(ray, results);
		octants[3]->query(ray, results);
		octants[4]->query(ray, results);
		octants[5]->query(ray, results);
		octants[6]->query(ray, results);
		octants[7]->query(ray, results);
	}
}

template <typename T>
inline const Octree<T>* Octree<T>::getOctant(std::size_t index) const
{
	return octants[index];
}

template <typename T>
inline Octree<T>* Octree<T>::getOctant(std::size_t index)
{
	return octants[index];
}

template <typename T>
inline const AABB& Octree<T>::getBounds() const
{
	return bounds;
}

template <typename T>
inline std::size_t Octree<T>::getDepth() const
{
	return depth;
}

template <typename T>
inline std::size_t Octree<T>::getMaxDepth() const
{
	return maxDepth;
}

} // namespace Emergent

#endif // EMERGENT_GEOMETRY_OCTREE_HPP
