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

#ifndef EMERGENT_GRAPHICS_TEXTURE_LOADER_HPP
#define EMERGENT_GRAPHICS_TEXTURE_LOADER_HPP

#include <string>

namespace Emergent
{

class Texture2D;
class TextureCube;

/**
 * Loads textures.
 *
 * @ingroup graphics
 */
class TextureLoader
{
public:
	/**
	 * Creates an instance of TextureLoader.
	 */
	TextureLoader();
	
	/**
	 * Loads a 2D texture.
	 *
	 * @param filename Path to the texture file.
	 * @return Pointer to the loaded texture, or `nullptr` if the texture could not be loaded.
	 */
	Texture2D* load2D(const std::string& filename);
	
	/**
	 * Loads a cube texture.
	 *
	 * @param filename Path to the texture file.
	 * @return Pointer to the loaded texture, or `nullptr` if the texture could not be loaded.
	 */
	TextureCube* loadCube(const std::string& filename);
	
	/**
	 * Sets the gamma correction exponent.
	 *
	 * @param gamma Gamma correction exponent. A value of `2.2` will convert textures stored in linear color-space to sRGB color-space. A value of `(1 / 2.2)` will convert textures stored in sRGB color-space to linear color-space. A value of `1.0` will leave the color-space untouched.
	 */
	void setGamma(float gamma);
	
	/**
	 * Enables or disables the mipmap chain loading flag. Only works for power-of-two textures. If mipmap chain loading is enabled, the `filename` parameter to TextureLoader::load() will be treated as a `sprintf` format string. The format string will be used to load each mipmap, with the index of the mipmap passed to `sprintf`. For a mipmap chain with `n` levels, the filename "cubemap_%d.hdr" will result in the files ["cubemap_0.hdr", "cubemap_1.hdr", ..., "cubemap_<n-1>.hdr"] being loaded.
	 *
	 * @param mipmapChain Specifies whether to enable mipmap chain loading.
	 */
	void setMipmapChain(bool mipmapChain);
	
	/**
	 * Sets the maximum degree of anisotropy. The initial value is `1.0`.
	 *
	 * @param anisotropy Maximum degree of anisotropy
	 */
	void setMaxAnisotropy(float anisotropy);
	
	/// Enables or disables repeating the texture S coordinates
	void setWrapS(bool repeat);
	
	/// Enables or disables repeating the texture T coordinates
	void setWrapT(bool repeat);
	
	/// Enables or disables repeating the texture R coordinates
	void setWrapR(bool repeat);
	
private:
	enum class CubemapLayout
	{
		VERTICAL_CROSS,
		HORIZONTAL_CROSS,
		VERTICAL_STRIP,
		HORIZONTAL_STRIP,
		BLENDER
	};
	
	static const int cubemapLayoutDimensions[5][2];
	static const int cubemapLayoutOffsets[5][6][2];
	static const bool cubemapLayoutFlips[5][6][2];
	
	bool loadMipmap(Texture2D* texture, const std::string& filename, int mipmapLevel);
	bool loadCubemapMipmap(TextureCube* texture, const std::string& filename, int mipmapLevel);
	bool loadMipmapChain(Texture2D* texture, const std::string& filename);
	bool loadCubemapMipmapChain(TextureCube* texture, const std::string& filename);
	
	float gamma;
	bool mipmapChain;
	float maxAnisotropy;
	bool wrapRepeatS;
	bool wrapRepeatT;
	bool wrapRepeatR;
};

} // namespace Emergent

#endif // EMERGENT_GRAPHICS_TEXTURE_LOADER_HPP
