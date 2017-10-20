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

#ifndef EMERGENT_FONT_FONT_HPP
#define EMERGENT_FONT_FONT_HPP

#include <emergent/font/font-metrics.hpp>
#include <emergent/font/glyph.hpp>
#include <emergent/font/kerning-table.hpp>
#include <emergent/graphics/texture.hpp>
#include <cstdlib>
#include <map>
#include <string>

namespace Emergent
{

class BillboardBatch;
class TextureAtlas;
class Image;

/**
 * Renders text to billboard batches
 *
 * @ingroup font
 */
class Font
{
public:
	/**
	 * Creates an instance of Font.
	 *
	 * @param width Specifies the width of the font texture.
	 * @param height Specifies the height of the font texture.
	 */
	Font(unsigned int width, unsigned int height);

	/**
	 * Destroys an instance of Font.
	 */
	~Font();
	
	/**
	 * Prints a string to a billboard batch.
	 *
	 * @param[out] batch Specifies a billboard batch.
	 * @param[in] translation Specifies the origin of the text
	 * @param[in] string Specifies a UTF-32 encoded string.
	 * @param[in] offset Specifies an offset to the index of the first billboard
	 * @param[out] count Returns the number of billboards written to the batch
	 */
	void puts(BillboardBatch* batch, const Vector3& origin, const std::u32string& string, const Vector4& color, std::size_t offset = 0, std::size_t* count = nullptr) const;
	
	/**
	 * Sets the font metrics.
	 *
	 * @param metrics Specifies font metrics.
	 */
	void setMetrics(const FontMetrics& metrics);

	/**
	 * Creates a glyph in the font.
	 *
	 * @param charcode Specifies the charcode of a glyph.
	 * @param metrics Specifies the glyph metrics.
	 * @param data Specifies the glyph image data.
	 * @param width Specifies the width of the image data, in pixels.
	 * @param height Specifies the height of the image data, in pixels.
	 *
	 * @return `true` if the glyph was successfully created, `false` otherwise.
	 */
	bool createGlyph(char32_t charcode, const GlyphMetrics& metrics, const unsigned char* data, unsigned int width, unsigned int height);

	/**
	 * Calculates the width of a string.
	 *
	 * @param string Specifies a UTF-32 string.
	 * @return Width of the string.
	 */
	float getWidth(const std::u32string& string) const;

	/**
	 * Returns the font metrics.
	 *
	 * @return Font metrics.
	 */
	const FontMetrics& getMetrics() const;

	/**
	 * Finds a glyph corresponding to the specified character code.
	 *
	 * @param charcode Specifies a character code.
	 *
	 * @return Pointer to the corresponding glyph, or `nullptr` if the glyph does not exist.
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
	const Texture* getTexture() const;
	
	/// @copydoc Font::getTexture() const
	Texture* getTexture();
	
private:
	FontMetrics fontMetrics;
	std::map<char32_t, Glyph> glyphs;
	KerningTable kerningTable;
	TextureAtlas* atlas;
	Texture texture;
};

inline void Font::setMetrics(const FontMetrics& metrics)
{
	this->fontMetrics = metrics;
}

inline const FontMetrics& Font::getMetrics() const
{
	return fontMetrics;
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

inline const Texture* Font::getTexture() const
{
	return &texture;
}

inline Texture* Font::getTexture()
{
	return &texture;
}

} // namespace Emergent

#endif // EMERGENT_FONT_FONT_HPP
