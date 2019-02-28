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

#ifndef EMERGENT_FONT_FONT_HPP
#define EMERGENT_FONT_FONT_HPP

#include <emergent/font/font-metrics.hpp>
#include <emergent/font/glyph.hpp>
#include <emergent/font/kerning-table.hpp>
#include <emergent/graphics/texture-2d.hpp>
#include <cstdlib>
#include <map>
#include <set>
#include <string>

namespace Emergent
{

class BillboardBatch;
class TexturePacker;
class Typeface;

/**
 * Renders text to billboard batches
 *
 * @ingroup font
 */
class Font
{
public:
	/**
	 * Creates a font.
	 *
	 * @param metrics Font metrics.
	 * @param width Width of the font texture, in pixels.
	 * @param height Height of the font texture, in pixels.
	 */
	Font(const FontMetrics& metrics, unsigned int width, unsigned int height);

	/**
	 * Destroys a font.
	 */
	~Font();
	
	/**
	 * Adds a glyph to the font.
	 *
	 * @param charcode Character code of the glyph being added.
	 * @param metrics Metrics of the glyph.
	 * @param data Glyph image data.
	 * @param width Width of the glyph image, in pixels.
	 * @param height Height of the glyph image, in pixels.
	 *
	 * @return `true` if the glyph was successfully created, `false` otherwise.
	 */
	bool addGlyph(char32_t charcode, const GlyphMetrics& metrics, const unsigned char* data, unsigned int width, unsigned int height);

	/**
	 * Prints a string to a billboard batch.
	 *
	 * @param[out] batch Specifies a billboard batch.
	 * @param[in] translation Specifies the origin of the text
	 * @param[in] string Specifies a UTF-32 encoded string.
	 * @param[in] offset Specifies an offset to the index of the first billboard
	 * @param[out] count Returns the number of billboards written to the batch
	 */
	void puts(BillboardBatch* batch, const Vector3& origin, const std::string& string, const Vector4& color, std::size_t offset = 0, std::size_t* count = nullptr) const;

	/**
	 * Calculates the width of a string encoded with UTF-8.
	 *
	 * @param string UTF-8 string.
	 * @return Width of the string, in pixels.
	 */
	float getWidth(const std::string& string) const;

	/**
	 * Returns the font metrics.
	 *
	 * @return Font metrics.
	 */
	const FontMetrics& getMetrics() const;

	/**
	 * Returns the set of characters which have been loaded into the font.
	 */
	const std::set<char32_t>& getCharset() const;

	/**
	 * Returns a glyph corresponding to the specified character code.
	 *
	 * @param charcode Character code corresponding to a glyph.
	 * @return Pointer to the corresponding glyph, or `nullptr` if the glyph for the specified character code has not been loaded.
	 */
	const Glyph* getGlyph(char32_t charcode) const;

	/**
	 * Returns the kerning table for the font.
	 *
	 * @return Kerning table for the font.
	 */
	const KerningTable* getKerningTable() const;

	/**
	 * @copydoc Font::getKerningTable() const
	 */
	KerningTable* getKerningTable();
	
	/**
	 * Returns the texture containing the font glyphs.
	 */
	const Texture2D* getTexture() const;
	
	/// @copydoc Font::getTexture() const
	Texture2D* getTexture();
	
private:
	FontMetrics metrics;
	std::set<char32_t> charset;
	std::map<char32_t, Glyph> glyphs;
	KerningTable kerningTable;
	TexturePacker* texturePacker;
	Texture2D texture;
};

inline const FontMetrics& Font::getMetrics() const
{
	return metrics;
}

inline const std::set<char32_t>& Font::getCharset() const
{
	return charset;
}

inline const Glyph* Font::getGlyph(char32_t charcode) const
{
	auto it = glyphs.find(charcode);
	if (it != glyphs.end())
	{
		return &(*it).second;
	}

	return nullptr;
}

inline const KerningTable* Font::getKerningTable() const
{
	return &kerningTable;
}

inline KerningTable* Font::getKerningTable()
{
	return &kerningTable;
}

inline const Texture2D* Font::getTexture() const
{
	return &texture;
}

inline Texture2D* Font::getTexture()
{
	return &texture;
}

} // namespace Emergent

#endif // EMERGENT_FONT_FONT_HPP

