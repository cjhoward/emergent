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

#ifndef EMERGENT_MATH_HASH_HPP
#define EMERGENT_MATH_HASH_HPP

#include <cstdlib>
#include <functional>

namespace Emergent
{

/**
 * Abstract base class for data types which can produce a hash value.
 *
 * @ingroup math
 */
class Hashable
{
public:
	std::size_t getHashValue() const;
	
protected:
	virtual void rehash() = 0;
	
	void setHashValue(std::size_t value);
	
	template <typename T>
	void addHashValue(const T& value);
	
private:
	static std::size_t combine(std::size_t lhs, std::size_t rhs);
	
	std::size_t hashValue;
};

inline void Hashable::setHashValue(std::size_t value)
{
	this->hashValue = value;
}

template <typename T>
void Hashable::addHashValue(const T& value)
{
	hashValue = combine(hashValue, std::hash<T>()(value));
}

inline std::size_t Hashable::getHashValue() const
{
	return hashValue;
}

inline std::size_t Hashable::combine(std::size_t lhs, std::size_t rhs)
{
	return rhs + 0x9e3779b9 + (lhs << 6) + (lhs >> 2);
}

} // namespace Emergent

#endif // EMERGENT_MATH_HASH_HPP
