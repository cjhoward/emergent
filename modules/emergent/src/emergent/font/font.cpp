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

#include <emergent/font/font.hpp>
#include <emergent/font/texture-packer.hpp>
#include <emergent/graphics/billboard.hpp>
#include <iostream>

namespace Emergent
{

Font::Font(unsigned int width, unsigned int height)
{
	GLuint textureID;
	
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	GLint swizzleMask[] = {GL_RED, GL_RED, GL_RED, GL_GREEN};
	glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_RGBA, swizzleMask);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RG8, width, height, 0, GL_RG, GL_UNSIGNED_BYTE, nullptr);
	//glGenerateMipmap(GL_TEXTURE_2D);
	
	texture.setTextureID(textureID);
	texture.setWidth(width);
	texture.setHeight(height);
	
	texturePacker = new TexturePacker(Rect(Vector2(0), Vector2(width, height)));
}

Font::~Font()
{
	delete texturePacker;
}

void Font::puts(BillboardBatch* batch, const Vector3& origin, const std::u32string& string, const Vector4& color, std::size_t offset, std::size_t* count) const
{
	if (count != nullptr)
	{
		*count = 0;
	}
	
	float cursorX = origin.x;
	float cursorY = origin.y + fontMetrics.getAscender();

	const Rect& packingBounds = texturePacker->getBounds();
	float atlasWidth = packingBounds.getWidth();
	float atlasHeight = packingBounds.getHeight();
	
	std::size_t currentBillboard = offset;
	char32_t previousCharacter = U'\0';
	
	for (std::size_t i = 0; i < string.size(); ++i)
	{
		char32_t character = string[i];
		
		if (character == U'\n')
		{
			cursorX = origin.x;
			cursorY += fontMetrics.getHeight();
			previousCharacter = character;

			continue;
		}

		auto it = glyphs.find(character);
		if (it == glyphs.end())
		{
			previousCharacter = character;
			continue;
		}
		
		// Apply kerning
		if (!kerningTable.isEmpty() && i > 0)
		{
			/// @TODO: vertical kerning			
			Vector2 kerning = kerningTable.getKerning(character, previousCharacter);
			cursorX += kerning[0];
		}

		const Glyph& glyph = (*it).second;
		
		const GlyphMetrics& glyphMetrics = glyph.getMetrics();
		
		Vector2 translation = Vector2(
			cursorX + glyphMetrics.getHorizontalBearing().x + glyphMetrics.getWidth() / 2.0f,
			cursorY - glyphMetrics.getHorizontalBearing().y + glyphMetrics.getHeight() / 2.0f);

		Vector2 textureCoordinatesMin = Vector2(
			glyph.getBounds().getMin().x / atlasWidth,
			glyph.getBounds().getMin().y / atlasHeight);
		Vector2 textureCoordinatesMax = Vector2(
			glyph.getBounds().getMax().x / atlasWidth,
			glyph.getBounds().getMax().y / atlasHeight);
		
		previousCharacter = character;
		
		// Add billboard to batch
		Billboard* billboard = batch->getBillboard(currentBillboard);
		billboard->setDimensions(Vector2(glyphMetrics.getWidth(), glyphMetrics.getHeight()));
		billboard->setTranslation(Vector3(translation.x, translation.y, origin.z));
		billboard->setTextureCoordinates(textureCoordinatesMin, textureCoordinatesMax);
		billboard->setTintColor(color);
		
		// Increment count
		if (count != nullptr)
		{
			++(*count);
		}
		
		// Increment cursor position
		cursorX += glyphMetrics.getHorizontalAdvance();
		
		// Incremen current billboard
		++currentBillboard;
	}
}

float Font::getWidth(const std::u32string& string) const
{
	float width = 0.0f;
	
	char32_t previous;
	for (std::size_t i = 0; i < string.size(); ++i)
	{
		char32_t current = string[i];
		
		// Find glyph
		auto it = glyphs.find(current);
		if (it == glyphs.end())
		{
			previous = current;
			continue;
		}

		// Add advance
		width += (*it).second.getMetrics().getHorizontalAdvance();
		
		// Apply kerning
		if (!kerningTable.isEmpty() && i > 0)
		{
			Vector2 kerning = kerningTable.getKerning(previous, current);

			width += kerning[0];
		}

		previous = current;
	}

	return width;
}

bool Font::createGlyph(char32_t charcode, const GlyphMetrics& metrics, const unsigned char* data, unsigned int width, unsigned int height)
{
	const TexturePackerNode* node = texturePacker->pack(width, height);
	if (!node)
	{
		return false;
	}
	
	const Rect& rect = node->getBounds();
	
	glBindTexture(GL_TEXTURE_2D, texture.getTextureID());
	
	// Update texture
	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexSubImage2D(GL_TEXTURE_2D, 0, static_cast<GLint>(rect.getMin().x), static_cast<GLint>(rect.getMin().y), width, height, GL_RG, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	
	Glyph& glyph = glyphs[charcode];
	glyph.setMetrics(metrics);
	glyph.setBounds(rect);

	return true;
}

} // namespace Emergent
