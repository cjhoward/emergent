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

#include <emergent/utility/unicode.hpp>
#include <codecvt>
#include <locale>

namespace Emergent
{

#if _MSC_VER >= 1900
	std::string toUTF8(const std::u16string& utf16)
	{
		std::string utf8;
		
		if (!utf16.empty())
		{
			std::wstring_convert<std::codecvt_utf8_utf16<int16_t>, int16_t> convert;
			const int16_t* data = reinterpret_cast<const int16_t*>(utf16.data());
			utf8 = convert.to_bytes(data, data + utf16.size());
		}
		
		return utf8;
	}

	std::string toUTF8(const std::u32string& utf32)
	{
		std::string utf8;
		
		if (!utf32.empty())
		{
			std::wstring_convert<std::codecvt_utf8<int32_t>, int32_t> convert;
			const int32_t* data = reinterpret_cast<const int32_t*>(utf32.data());
			utf8 = convert.to_bytes(data, data + utf32.size());
		}
		
		return utf8;
	}

	std::u16string toUTF16(const std::string& utf8)
	{
		std::u16string utf16;
		
		if (!utf8.empty())
		{
			std::wstring_convert<std::codecvt_utf8_utf16<int16_t>, int16_t> convert;
			std::basic_string<int16_t> string = convert.from_bytes(utf8.data(), utf8.data() + utf8.size());
			utf16 = reinterpret_cast<const char16_t*>(string.data());
		}
		
		return utf16;
	}

	std::u16string toUTF16(const std::u32string& utf32)
	{
		return toUTF16(toUTF8(utf32));
	}

	std::u32string toUTF32(const std::string& utf8)
	{
		std::u32string utf32;
		
		if (!utf8.empty())
		{
			std::wstring_convert<std::codecvt_utf8<int32_t>, int32_t> convert;
			std::basic_string<int32_t> string = convert.from_bytes(utf8.data(), utf8.data() + utf8.size());
			utf32 = reinterpret_cast<const char32_t *>(string.data());
		}
		
		return utf32;
	}

	std::u32string toUTF32(const std::u16string& utf16)
	{
		return toUTF32(toUTF8(utf16));
	}
#else
	std::string toUTF8(const std::u16string& utf16)
	{
		std::string utf8;
		
		if (!utf16.empty())
		{
			std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> convert;
			utf8 = convert.to_bytes(utf16);
		}
		
		return utf8;
	}

	std::string toUTF8(const std::u32string& utf32)
	{
		std::string utf8;
		
		if (!utf32.empty())
		{
			std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> convert;
			utf8 = convert.to_bytes(utf32);
		}
		
		return utf8;
	}

	std::u16string toUTF16(const std::string& utf8)
	{
		std::u16string utf16;
		
		if (!utf8.empty())
		{
			std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> convert;
			utf16 = convert.from_bytes(utf8);
		}
		
		return utf16;
	}

	std::u16string toUTF16(const std::u32string& utf32)
	{
		std::u16string utf16;
		
		if (!utf32.empty())
		{
			std::wstring_convert<std::codecvt_utf16<char32_t>, char32_t> convert;
			std::string bytes = convert.to_bytes(utf32);
			utf16 = std::u16string(reinterpret_cast<const char16_t*>(bytes.c_str()), bytes.length() / sizeof(char16_t));
		}
		
		return utf16;
	}

	std::u32string toUTF32(const std::string& utf8)
	{
		std::u32string utf32;
		
		if (!utf8.empty())
		{
			std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> convert;
			utf32 = convert.from_bytes(utf8);
		}
		
		return utf32;
	}

	std::u32string toUTF32(const std::u16string& utf16)
	{
		std::u32string utf32;
		
		if (!utf16.empty())
		{
			const char16_t* data = utf16.c_str();
			std::wstring_convert<std::codecvt_utf16<char32_t>, char32_t> convert;
			utf32 = convert.from_bytes(reinterpret_cast<const char*>(data), reinterpret_cast<const char*>(data + utf16.length()));
		}
		
		return utf32;
	}
#endif

} // namespace Emergent
