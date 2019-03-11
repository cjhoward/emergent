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

#ifndef EMERGENT_UTILITY_UNICODE_HPP
#define EMERGENT_UTILITY_UNICODE_HPP

#include <string>

namespace Emergent
{

/// Converts a UTF-16 string to a UTF-8 string.
std::string toUTF8(const std::u16string& utf16);

/// Converts a UTF-32 string to a UTF-8 string.
std::string toUTF8(const std::u32string& utf32);

/// Converts a UTF-8 string to a UTF-16 string.
std::u16string toUTF16(const std::string& utf8);

/// Converts a UTF-32 string to a UTF-16 string.
std::u16string toUTF16(const std::u32string& utf32);

/// Converts a UTF-8 string to a UTF-32 string.
std::u32string toUTF32(const std::string& utf8);

/// Converts a UTF-16 string to a UTF-32 string.
std::u32string toUTF32(const std::u16string& utf16);

} // namespace Emergent

#endif // EMERGENT_UTILITY_UNICODE_HPP
