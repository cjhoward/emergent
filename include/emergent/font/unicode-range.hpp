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

#ifndef EMERGENT_FONT_UNICODE_RANGE_HPP
#define EMERGENT_FONT_UNICODE_RANGE_HPP

namespace Emergent
{

/**
 * Defines a range of Unicode characters.
 *
 * @see https://en.wikipedia.org/wiki/Unicode_block
 * @see http://jrgraphix.net/research/unicode.php
 *
 * @ingroup font
 */
struct UnicodeRange
{
public:
	/**
	 * Creates an instance of UnicodeRange.
	 *
	 * @param start First character in the range.
	 * @param end Last character in the range.
	 */
	UnicodeRange(char32_t start, char32_t end);
	
	/**
	 * Creates an instance of UnicodeRange.
	 *
	 * @param character Single character which is the start and end of the range.
	 */
	UnicodeRange(char32_t character);
	
	char32_t start;
	char32_t end;
	
	static const UnicodeRange BASIC_LATIN;
	static const UnicodeRange LATIN_1_SUPPLEMENT;
	static const UnicodeRange LATIN_EXTENDED_A;
	static const UnicodeRange LATIN_EXTENDED_B;
	static const UnicodeRange IPA_EXTENSIONS;
	static const UnicodeRange SPACING_MODIFIER_LETTERS;
	static const UnicodeRange COMBINING_DIACRITICAL_MARKS;
	static const UnicodeRange GREEK_AND_COPTIC;
	static const UnicodeRange CYRILLIC;
	static const UnicodeRange CYRILLIC_SUPPLEMENTARY;
	static const UnicodeRange ARMENIAN;
	static const UnicodeRange HEBREW;
	static const UnicodeRange ARABIC;
	static const UnicodeRange SYRIAC;
	static const UnicodeRange THAANA;
	static const UnicodeRange DEVANAGARI;
	static const UnicodeRange BENGALI;
	static const UnicodeRange GURMUKHI;
	static const UnicodeRange GUJARATI;
	static const UnicodeRange ORIYA;
	static const UnicodeRange TAMIL;
	static const UnicodeRange TELUGU;
	static const UnicodeRange KANNADA;
	static const UnicodeRange MALAYALAM;
	static const UnicodeRange SINHALA;
	static const UnicodeRange THAI;
	static const UnicodeRange LAO;
	static const UnicodeRange TIBETAN;
	static const UnicodeRange MYANMAR;
	static const UnicodeRange GEORGIAN;
	static const UnicodeRange HANGUL_JAMO;
	static const UnicodeRange ETHIOPIC;
	static const UnicodeRange CHEROKEE;
	static const UnicodeRange UNIFIED_CANADIAN_ABORIGINAL_SYLLABICS;
	static const UnicodeRange OGHAM;
	static const UnicodeRange RUNIC;
	static const UnicodeRange TAGALOG;
	static const UnicodeRange HANUNOO;
	static const UnicodeRange BUHID;
	static const UnicodeRange TAGBANWA;
	static const UnicodeRange KHMER;
	static const UnicodeRange MONGOLIAN;
	static const UnicodeRange LIMBU;
	static const UnicodeRange TAI_LE;
	static const UnicodeRange KHMER_SYMBOLS;
	static const UnicodeRange PHONETIC_EXTENSIONS;
	static const UnicodeRange LATIN_EXTENDED_ADDITIONAL;
	static const UnicodeRange GREEK_EXTENDED;
	static const UnicodeRange GENERAL_PUNCTUATION;
	static const UnicodeRange SUPERSCRIPTS_AND_SUBSCRIPTS;
	static const UnicodeRange CURRENCY_SYMBOLS;
	static const UnicodeRange COMBINING_DIACRITICAL_MARKS_FOR_SYMBOLS;
	static const UnicodeRange LETTERLIKE_SYMBOLS;
	static const UnicodeRange NUMBER_FORMS;
	static const UnicodeRange ARROWS;
	static const UnicodeRange MATHEMATICAL_OPERATORS;
	static const UnicodeRange MISCELLANEOUS_TECHNICAL;
	static const UnicodeRange CONTROL_PICTURES;
	static const UnicodeRange OPTICAL_CHARACTER_RECOGNITION;
	static const UnicodeRange ENCLOSED_ALPHANUMERICS;
	static const UnicodeRange BOX_DRAWING;
	static const UnicodeRange BLOCK_ELEMENTS;
	static const UnicodeRange GEOMETRIC_SHAPES;
	static const UnicodeRange MISCELLANEOUS_SYMBOLS;
	static const UnicodeRange DINGBATS;
	static const UnicodeRange MISCELLANEOUS_MATHEMATICAL_SYMBOLS_A;
	static const UnicodeRange SUPPLEMENTAL_ARROWS_A;
	static const UnicodeRange BRAILLE_PATTERNS;
	static const UnicodeRange SUPPLEMENTAL_ARROWS_B;
	static const UnicodeRange MISCELLANEOUS_MATHEMATICAL_SYMBOLS_B;
	static const UnicodeRange SUPPLEMENTAL_MATHEMATICAL_OPERATORS;
	static const UnicodeRange MISCELLANEOUS_SYMBOLS_AND_ARROWS;
	static const UnicodeRange CJK_RADICALS_SUPPLEMENT;
	static const UnicodeRange KANGXI_RADICALS;
	static const UnicodeRange IDEOGRAPHIC_DESCRIPTION_CHARACTERS;
	static const UnicodeRange CJK_SYMBOLS_AND_PUNCTUATION;
	static const UnicodeRange HIRAGANA;
	static const UnicodeRange KATAKANA;
	static const UnicodeRange BOPOMOFO;
	static const UnicodeRange HANGUL_COMPATIBILITY_JAMO;
	static const UnicodeRange KANBUN;
	static const UnicodeRange BOPOMOFO_EXTENDED;
	static const UnicodeRange KATAKANA_PHONETIC_EXTENSIONS;
	static const UnicodeRange ENCLOSED_CJK_LETTERS_AND_MONTHS;
	static const UnicodeRange CJK_COMPATIBILITY;
	static const UnicodeRange CJK_UNIFIED_IDEOGRAPHS_EXTENSION_A;
	static const UnicodeRange YIJING_HEXAGRAM_SYMBOLS;
	static const UnicodeRange CJK_UNIFIED_IDEOGRAPHS;
	static const UnicodeRange YI_SYLLABLES;
	static const UnicodeRange YI_RADICALS;
	static const UnicodeRange HANGUL_SYLLABLES;
	static const UnicodeRange HIGH_SURROGATES;
	static const UnicodeRange HIGH_PRIVATE_USE_SURROGATES;
	static const UnicodeRange LOW_SURROGATES;
	static const UnicodeRange PRIVATE_USE_AREA;
	static const UnicodeRange CJK_COMPATIBILITY_IDEOGRAPHS;
	static const UnicodeRange ALPHABETIC_PRESENTATION_FORMS;
	static const UnicodeRange ARABIC_PRESENTATION_FORMS_A;
	static const UnicodeRange VARIATION_SELECTORS;
	static const UnicodeRange COMBINING_HALF_MARKS;
	static const UnicodeRange CJK_COMPATIBILITY_FORMS;
	static const UnicodeRange SMALL_FORM_VARIANTS;
	static const UnicodeRange ARABIC_PRESENTATION_FORMS_B;
	static const UnicodeRange HALFWIDTH_AND_FULLWIDTH_FORMS;
	static const UnicodeRange SPECIALS;
	static const UnicodeRange LINEAR_B_SYLLABARY;
	static const UnicodeRange LINEAR_B_IDEOGRAMS;
	static const UnicodeRange AEGEAN_NUMBERS;
	static const UnicodeRange OLD_ITALIC;
	static const UnicodeRange GOTHIC;
	static const UnicodeRange UGARITIC;
	static const UnicodeRange DESERET;
	static const UnicodeRange SHAVIAN;
	static const UnicodeRange OSMANYA;
	static const UnicodeRange CYPRIOT_SYLLABARY;
	static const UnicodeRange BYZANTINE_MUSICAL_SYMBOLS;
	static const UnicodeRange MUSICAL_SYMBOLS;
	static const UnicodeRange TAI_XUAN_JING_SYMBOLS;
	static const UnicodeRange MATHEMATICAL_ALPHANUMERIC_SYMBOLS;
	static const UnicodeRange CJK_UNIFIED_IDEOGRAPHS_EXTENSION_B;
	static const UnicodeRange CJK_COMPATIBILITY_IDEOGRAPHS_SUPPLEMENT;
	static const UnicodeRange TAGS;
};

inline UnicodeRange::UnicodeRange(char32_t start, char32_t end):
	start(start),
	end(end)
{}

inline UnicodeRange::UnicodeRange(char32_t character):
	start(character),
	end(character)
{}

} // namespace Emergent

#endif // EMERGENT_FONT_UNICODE_RANGE_HPP
