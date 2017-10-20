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

#include <emergent/font/unicode-range.hpp>

namespace Emergent
{

const UnicodeRange UnicodeRange::BASIC_LATIN(U'\U00000020', U'\U0000007F');
const UnicodeRange UnicodeRange::LATIN_1_SUPPLEMENT(U'\U000000A0', U'\U000000FF');
const UnicodeRange UnicodeRange::LATIN_EXTENDED_A(U'\U00000100', U'\U0000017F');
const UnicodeRange UnicodeRange::LATIN_EXTENDED_B(U'\U00000180', U'\U0000024F');
const UnicodeRange UnicodeRange::IPA_EXTENSIONS(U'\U00000250', U'\U000002AF');
const UnicodeRange UnicodeRange::SPACING_MODIFIER_LETTERS(U'\U000002B0', U'\U000002FF');
const UnicodeRange UnicodeRange::COMBINING_DIACRITICAL_MARKS(U'\U00000300', U'\U0000036F');
const UnicodeRange UnicodeRange::GREEK_AND_COPTIC(U'\U00000370', U'\U000003FF');
const UnicodeRange UnicodeRange::CYRILLIC(U'\U00000400', U'\U000004FF');
const UnicodeRange UnicodeRange::CYRILLIC_SUPPLEMENTARY(U'\U00000500', U'\U0000052F');
const UnicodeRange UnicodeRange::ARMENIAN(U'\U00000530', U'\U0000058F');
const UnicodeRange UnicodeRange::HEBREW(U'\U00000590', U'\U000005FF');
const UnicodeRange UnicodeRange::ARABIC(U'\U00000600', U'\U000006FF');
const UnicodeRange UnicodeRange::SYRIAC(U'\U00000700', U'\U0000074F');
const UnicodeRange UnicodeRange::THAANA(U'\U00000780', U'\U000007BF');
const UnicodeRange UnicodeRange::DEVANAGARI(U'\U00000900', U'\U0000097F');
const UnicodeRange UnicodeRange::BENGALI(U'\U00000980', U'\U000009FF');
const UnicodeRange UnicodeRange::GURMUKHI(U'\U00000A00', U'\U00000A7F');
const UnicodeRange UnicodeRange::GUJARATI(U'\U00000A80', U'\U00000AFF');
const UnicodeRange UnicodeRange::ORIYA(U'\U00000B00', U'\U00000B7F');
const UnicodeRange UnicodeRange::TAMIL(U'\U00000B80', U'\U00000BFF');
const UnicodeRange UnicodeRange::TELUGU(U'\U00000C00', U'\U00000C7F');
const UnicodeRange UnicodeRange::KANNADA(U'\U00000C80', U'\U00000CFF');
const UnicodeRange UnicodeRange::MALAYALAM(U'\U00000D00', U'\U00000D7F');
const UnicodeRange UnicodeRange::SINHALA(U'\U00000D80', U'\U00000DFF');
const UnicodeRange UnicodeRange::THAI(U'\U00000E00', U'\U00000E7F');
const UnicodeRange UnicodeRange::LAO(U'\U00000E80', U'\U00000EFF');
const UnicodeRange UnicodeRange::TIBETAN(U'\U00000F00', U'\U00000FFF');
const UnicodeRange UnicodeRange::MYANMAR(U'\U00001000', U'\U0000109F');
const UnicodeRange UnicodeRange::GEORGIAN(U'\U000010A0', U'\U000010FF');
const UnicodeRange UnicodeRange::HANGUL_JAMO(U'\U00001100', U'\U000011FF');
const UnicodeRange UnicodeRange::ETHIOPIC(U'\U00001200', U'\U0000137F');
const UnicodeRange UnicodeRange::CHEROKEE(U'\U000013A0', U'\U000013FF');
const UnicodeRange UnicodeRange::UNIFIED_CANADIAN_ABORIGINAL_SYLLABICS(U'\U00001400', U'\U0000167F');
const UnicodeRange UnicodeRange::OGHAM(U'\U00001680', U'\U0000169F');
const UnicodeRange UnicodeRange::RUNIC(U'\U000016A0', U'\U000016FF');
const UnicodeRange UnicodeRange::TAGALOG(U'\U00001700', U'\U0000171F');
const UnicodeRange UnicodeRange::HANUNOO(U'\U00001720', U'\U0000173F');
const UnicodeRange UnicodeRange::BUHID(U'\U00001740', U'\U0000175F');
const UnicodeRange UnicodeRange::TAGBANWA(U'\U00001760', U'\U0000177F');
const UnicodeRange UnicodeRange::KHMER(U'\U00001780', U'\U000017FF');
const UnicodeRange UnicodeRange::MONGOLIAN(U'\U00001800', U'\U000018AF');
const UnicodeRange UnicodeRange::LIMBU(U'\U00001900', U'\U0000194F');
const UnicodeRange UnicodeRange::TAI_LE(U'\U00001950', U'\U0000197F');
const UnicodeRange UnicodeRange::KHMER_SYMBOLS(U'\U000019E0', U'\U000019FF');
const UnicodeRange UnicodeRange::PHONETIC_EXTENSIONS(U'\U00001D00', U'\U00001D7F');
const UnicodeRange UnicodeRange::LATIN_EXTENDED_ADDITIONAL(U'\U00001E00', U'\U00001EFF');
const UnicodeRange UnicodeRange::GREEK_EXTENDED(U'\U00001F00', U'\U00001FFF');
const UnicodeRange UnicodeRange::GENERAL_PUNCTUATION(U'\U00002000', U'\U0000206F');
const UnicodeRange UnicodeRange::SUPERSCRIPTS_AND_SUBSCRIPTS(U'\U00002070', U'\U0000209F');
const UnicodeRange UnicodeRange::CURRENCY_SYMBOLS(U'\U000020A0', U'\U000020CF');
const UnicodeRange UnicodeRange::COMBINING_DIACRITICAL_MARKS_FOR_SYMBOLS(U'\U000020D0', U'\U000020FF');
const UnicodeRange UnicodeRange::LETTERLIKE_SYMBOLS(U'\U00002100', U'\U0000214F');
const UnicodeRange UnicodeRange::NUMBER_FORMS(U'\U00002150', U'\U0000218F');
const UnicodeRange UnicodeRange::ARROWS(U'\U00002190', U'\U000021FF');
const UnicodeRange UnicodeRange::MATHEMATICAL_OPERATORS(U'\U00002200', U'\U000022FF');
const UnicodeRange UnicodeRange::MISCELLANEOUS_TECHNICAL(U'\U00002300', U'\U000023FF');
const UnicodeRange UnicodeRange::CONTROL_PICTURES(U'\U00002400', U'\U0000243F');
const UnicodeRange UnicodeRange::OPTICAL_CHARACTER_RECOGNITION(U'\U00002440', U'\U0000245F');
const UnicodeRange UnicodeRange::ENCLOSED_ALPHANUMERICS(U'\U00002460', U'\U000024FF');
const UnicodeRange UnicodeRange::BOX_DRAWING(U'\U00002500', U'\U0000257F');
const UnicodeRange UnicodeRange::BLOCK_ELEMENTS(U'\U00002580', U'\U0000259F');
const UnicodeRange UnicodeRange::GEOMETRIC_SHAPES(U'\U000025A0', U'\U000025FF');
const UnicodeRange UnicodeRange::MISCELLANEOUS_SYMBOLS(U'\U00002600', U'\U000026FF');
const UnicodeRange UnicodeRange::DINGBATS(U'\U00002700', U'\U000027BF');
const UnicodeRange UnicodeRange::MISCELLANEOUS_MATHEMATICAL_SYMBOLS_A(U'\U000027C0', U'\U000027EF');
const UnicodeRange UnicodeRange::SUPPLEMENTAL_ARROWS_A(U'\U000027F0', U'\U000027FF');
const UnicodeRange UnicodeRange::BRAILLE_PATTERNS(U'\U00002800', U'\U000028FF');
const UnicodeRange UnicodeRange::SUPPLEMENTAL_ARROWS_B(U'\U00002900', U'\U0000297F');
const UnicodeRange UnicodeRange::MISCELLANEOUS_MATHEMATICAL_SYMBOLS_B(U'\U00002980', U'\U000029FF');
const UnicodeRange UnicodeRange::SUPPLEMENTAL_MATHEMATICAL_OPERATORS(U'\U00002A00', U'\U00002AFF');
const UnicodeRange UnicodeRange::MISCELLANEOUS_SYMBOLS_AND_ARROWS(U'\U00002B00', U'\U00002BFF');
const UnicodeRange UnicodeRange::CJK_RADICALS_SUPPLEMENT(U'\U00002E80', U'\U00002EFF');
const UnicodeRange UnicodeRange::KANGXI_RADICALS(U'\U00002F00', U'\U00002FDF');
const UnicodeRange UnicodeRange::IDEOGRAPHIC_DESCRIPTION_CHARACTERS(U'\U00002FF0', U'\U00002FFF');
const UnicodeRange UnicodeRange::CJK_SYMBOLS_AND_PUNCTUATION(U'\U00003000', U'\U0000303F');
const UnicodeRange UnicodeRange::HIRAGANA(U'\U00003040', U'\U0000309F');
const UnicodeRange UnicodeRange::KATAKANA(U'\U000030A0', U'\U000030FF');
const UnicodeRange UnicodeRange::BOPOMOFO(U'\U00003100', U'\U0000312F');
const UnicodeRange UnicodeRange::HANGUL_COMPATIBILITY_JAMO(U'\U00003130', U'\U0000318F');
const UnicodeRange UnicodeRange::KANBUN(U'\U00003190', U'\U0000319F');
const UnicodeRange UnicodeRange::BOPOMOFO_EXTENDED(U'\U000031A0', U'\U000031BF');
const UnicodeRange UnicodeRange::KATAKANA_PHONETIC_EXTENSIONS(U'\U000031F0', U'\U000031FF');
const UnicodeRange UnicodeRange::ENCLOSED_CJK_LETTERS_AND_MONTHS(U'\U00003200', U'\U000032FF');
const UnicodeRange UnicodeRange::CJK_COMPATIBILITY(U'\U00003300', U'\U000033FF');
const UnicodeRange UnicodeRange::CJK_UNIFIED_IDEOGRAPHS_EXTENSION_A(U'\U00003400', U'\U00004DBF');
const UnicodeRange UnicodeRange::YIJING_HEXAGRAM_SYMBOLS(U'\U00004DC0', U'\U00004DFF');
const UnicodeRange UnicodeRange::CJK_UNIFIED_IDEOGRAPHS(U'\U00004E00', U'\U00009FFF');
const UnicodeRange UnicodeRange::YI_SYLLABLES(U'\U0000A000', U'\U0000A48F');
const UnicodeRange UnicodeRange::YI_RADICALS(U'\U0000A490', U'\U0000A4CF');
const UnicodeRange UnicodeRange::HANGUL_SYLLABLES(U'\U0000AC00', U'\U0000D7AF');
const UnicodeRange UnicodeRange::HIGH_SURROGATES(static_cast<char32_t>(0x0000D800), static_cast<char32_t>(0x0000DB7F));
const UnicodeRange UnicodeRange::HIGH_PRIVATE_USE_SURROGATES(static_cast<char32_t>(0x0000DB80), static_cast<char32_t>(0x0000DBFF));
const UnicodeRange UnicodeRange::LOW_SURROGATES(static_cast<char32_t>(0x0000DC00), static_cast<char32_t>(0x0000DFFF));
const UnicodeRange UnicodeRange::PRIVATE_USE_AREA(U'\U0000E000', U'\U0000F8FF');
const UnicodeRange UnicodeRange::CJK_COMPATIBILITY_IDEOGRAPHS(U'\U0000F900', U'\U0000FAFF');
const UnicodeRange UnicodeRange::ALPHABETIC_PRESENTATION_FORMS(U'\U0000FB00', U'\U0000FB4F');
const UnicodeRange UnicodeRange::ARABIC_PRESENTATION_FORMS_A(U'\U0000FB50', U'\U0000FDFF');
const UnicodeRange UnicodeRange::VARIATION_SELECTORS(U'\U0000FE00', U'\U0000FE0F');
const UnicodeRange UnicodeRange::COMBINING_HALF_MARKS(U'\U0000FE20', U'\U0000FE2F');
const UnicodeRange UnicodeRange::CJK_COMPATIBILITY_FORMS(U'\U0000FE30', U'\U0000FE4F');
const UnicodeRange UnicodeRange::SMALL_FORM_VARIANTS(U'\U0000FE50', U'\U0000FE6F');
const UnicodeRange UnicodeRange::ARABIC_PRESENTATION_FORMS_B(U'\U0000FE70', U'\U0000FEFF');
const UnicodeRange UnicodeRange::HALFWIDTH_AND_FULLWIDTH_FORMS(U'\U0000FF00', U'\U0000FFEF');
const UnicodeRange UnicodeRange::SPECIALS(U'\U0000FFF0', U'\U0000FFFF');
const UnicodeRange UnicodeRange::LINEAR_B_SYLLABARY(U'\U00010000', U'\U0001007F');
const UnicodeRange UnicodeRange::LINEAR_B_IDEOGRAMS(U'\U00010080', U'\U000100FF');
const UnicodeRange UnicodeRange::AEGEAN_NUMBERS(U'\U00010100', U'\U0001013F');
const UnicodeRange UnicodeRange::OLD_ITALIC(U'\U00010300', U'\U0001032F');
const UnicodeRange UnicodeRange::GOTHIC(U'\U00010330', U'\U0001034F');
const UnicodeRange UnicodeRange::UGARITIC(U'\U00010380', U'\U0001039F');
const UnicodeRange UnicodeRange::DESERET(U'\U00010400', U'\U0001044F');
const UnicodeRange UnicodeRange::SHAVIAN(U'\U00010450', U'\U0001047F');
const UnicodeRange UnicodeRange::OSMANYA(U'\U00010480', U'\U000104AF');
const UnicodeRange UnicodeRange::CYPRIOT_SYLLABARY(U'\U00010800', U'\U0001083F');
const UnicodeRange UnicodeRange::BYZANTINE_MUSICAL_SYMBOLS(U'\U0001D000', U'\U0001D0FF');
const UnicodeRange UnicodeRange::MUSICAL_SYMBOLS(U'\U0001D100', U'\U0001D1FF');
const UnicodeRange UnicodeRange::TAI_XUAN_JING_SYMBOLS(U'\U0001D300', U'\U0001D35F');
const UnicodeRange UnicodeRange::MATHEMATICAL_ALPHANUMERIC_SYMBOLS(U'\U0001D400', U'\U0001D7FF');
const UnicodeRange UnicodeRange::CJK_UNIFIED_IDEOGRAPHS_EXTENSION_B(U'\U00020000', U'\U0002A6DF');
const UnicodeRange UnicodeRange::CJK_COMPATIBILITY_IDEOGRAPHS_SUPPLEMENT(U'\U0002F800', U'\U0002FA1F');
const UnicodeRange UnicodeRange::TAGS(U'\U000E0000', U'\U000E007F');

} // namespace Emergent
