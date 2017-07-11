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

#include <emergent/graphics/texture-loader.hpp>
#include <emergent/graphics/texture.hpp>
#include <emergent/graphics/stb-image.hpp>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>

// Anisotropic filtering is not part of the OpenGL core
#define GL_TEXTURE_MAX_ANISOTROPY_EXT 0x84FE
#define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT 0x84FF
 
namespace Emergent
{

const int TextureLoader::cubemapLayoutDimensions[5][2] = 
{
	{3, 4}, // Vertical cross
	{4, 3}, // Horizontal cross
	{1, 6}, // Vertical strip
	{6, 1}, // Horizontal strip
	{3, 2}  // Blender
};

const int TextureLoader::cubemapLayoutOffsets[5][6][2] = 
{
	// Vertical cross
	{
		{0, 1}, // +X
		{2, 1}, // -X
		{1, 0}, // +Y
		{1, 2}, // -Y
		{1, 1}, // +Z
		{1, 3}  // -Z
	},
	
	// Horizontal cross
	{
		{0, 1}, // +X
		{2, 1}, // -X
		{1, 0}, // +Y
		{1, 2}, // -Y
		{1, 1}, // +Z
		{3, 1}  // -Z
	},
	
	// Vertical strip
	{
		{0, 1}, // +X
		{0, 0}, // -X
		{0, 2}, // +Y
		{0, 3}, // -Y
		{0, 4}, // +Z
		{0, 5}  // -Z
	},
	
	// Horizontal strip
	{
		{1, 0}, // +X
		{0, 0}, // -X
		{2, 0}, // +Y
		{3, 0}, // -Y
		{4, 0}, // +Z
		{5, 0}  // -Z
	},
	
	// Blender
	{
		{0, 0}, // +X
		{2, 0}, // -X
		{1, 1}, // +Y
		{0, 1}, // -Y
		{1, 0}, // +Z
		{2, 1}  // -Z
	}
};

const bool TextureLoader::cubemapLayoutFlips[5][6][2] = 
{
	// Vertical cross
	{
		{true, true}, // +X
		{true, true}, // -X
		{true, true}, // +Y
		{true, true}, // -Y
		{true, true}, // +Z
		{false, false}, // -Z
	},
	
	// Horizontal cross
	{
		{true, true}, // +X
		{true, true}, // -X
		{true, true}, // +Y
		{true, true}, // -Y
		{true, true}, // +Z
		{true, true}, // -Z
	},
	
	// Vertical strip
	{
		{true, true}, // +X
		{true, true}, // -X
		{true, true}, // +Y
		{true, true}, // -Y
		{true, true}, // +Z
		{true, true}, // -Z
	},
	
	// Horizontal strip
	{
		{true, true}, // +X
		{true, true}, // -X
		{true, true}, // +Y
		{true, true}, // -Y
		{true, true}, // +Z
		{true, true}, // -Z
	},
	
	// Blender
	{
		{true, true}, // +X
		{true, true}, // -X
		{true, true}, // +Y
		{true, true}, // -Y
		{true, true}, // +Z
		{true, true}, // -Z
	}
};

TextureLoader::TextureLoader():
	gamma(1.0f),
	mipmapChain(false),
	cubemap(false),
	maxAnisotropy(1.0f),
	wrapRepeatS(true),
	wrapRepeatT(true),
	wrapRepeatR(true)
{}

Texture* TextureLoader::load(const std::string& filename)
{
	// Check cubemap loading flag
	if (cubemap)
	{
		// Load cubemap
		return loadCubemap(filename);
	}
	
	// Generate OpenGL texture ID
	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	
	// Set wrapping and filtering parameters
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (wrapRepeatS) ? GL_REPEAT : GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (wrapRepeatT) ? GL_REPEAT : GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	// Set anisotropic filtering
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, maxAnisotropy);
	
	// Allocate texture and set its texture ID
	Texture* texture = new Texture();
	texture->setTextureID(textureID);
	
	// Check mipmap chain loading flag
	if (mipmapChain)
	{
		// Load mipmap chain
		if (!loadMipmapChain(texture, filename))
		{
			delete texture;
			return nullptr;
		}
	}
	else
	{
		// Load texture
		if (!loadMipmap(texture, filename, 0))
		{
			delete texture;
			return nullptr;
		}
		
		// Automatically generate mipmaps
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	return texture;
}

void TextureLoader::setGamma(float gamma)
{
	this->gamma = gamma;
}

void TextureLoader::setMipmapChain(bool mipmapChain)
{
	this->mipmapChain = mipmapChain;
}

void TextureLoader::setCubemap(bool cubemap)
{
	this->cubemap = cubemap;
}

void TextureLoader::setMaxAnisotropy(float anisotropy)
{
	this->maxAnisotropy = anisotropy;
}

void TextureLoader::setWrapS(bool repeat)
{
	this->wrapRepeatS = repeat;
}

void TextureLoader::setWrapT(bool repeat)
{
	this->wrapRepeatT = repeat;
}

void TextureLoader::setWrapR(bool repeat)
{
	this->wrapRepeatR = repeat;
}

Texture* TextureLoader::loadCubemap(const std::string& filename)
{
	// Generate OpenGL texture ID
	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	
	// Set wrapping and filtering parameters
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, (wrapRepeatS) ? GL_REPEAT : GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, (wrapRepeatT) ? GL_REPEAT : GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, (wrapRepeatR) ? GL_REPEAT : GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	// Allocate texture and set its texture ID
	Texture* texture = new Texture();
	texture->setTextureID(textureID);
	
	// Check mipmap chain loading flag
	if (mipmapChain)
	{
		// Load cubemap mipmap chain
		if (!loadMipmapChain(texture, filename))
		{
			delete texture;
			return nullptr;
		}
	}
	else
	{
		// Load cubemap
		if (!loadCubemapMipmap(texture, filename, 0))
		{
			delete texture;
			return nullptr;
		}
		
		// Automatically generate mipmaps
		glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
	}
	
	return texture;
}

bool TextureLoader::loadMipmap(Texture* texture, const std::string& filename, int mipmapLevel)
{
	int width;
	int height;
	int channels;
	
	// Determine if image is in an HDR format
	bool hdr = (stbi_is_hdr(filename.c_str()) != 0);
	
	// Set vertical flip on load in order to upload pixels correctly to OpenGL
	stbi_set_flip_vertically_on_load(true);
	
	// Load image data
	void* pixels = nullptr;
	if (hdr)
	{
		pixels = stbi_loadf(filename.c_str(), &width, &height, &channels, 0);
	}
	else
	{
		pixels = stbi_load(filename.c_str(), &width, &height, &channels, 0);
	}
	
	// Check if image was loaded
	if (!pixels)
	{
		std::cerr << "TextureLoader::loadMipmap(): Failed to load mipmap level " << mipmapLevel << " from \"" << filename << "\"" << std::endl;
		return false;
	}
	
	// If this is the base-level mipmap, set the texture dimensions
	if (!mipmapLevel)
	{
		texture->setWidth(width);
		texture->setHeight(height);
	}
	else
	{
		// Verify mipmap dimensions
		if (width != texture->getWidth() >> mipmapLevel ||
			height != texture->getHeight() >> mipmapLevel)
		{
			std::cerr << "TextureLoader::loadMipmap(): Mipmap level " << mipmapLevel << " loaded from \"" << filename << "\" has incorrect dimensions" << std::endl;
			stbi_image_free(pixels);
			return false;
		}
	}
	
	// Select texture formats according to number of color channels in the image
	GLint internalFormat;
	GLenum format;
	GLenum type = (hdr) ? GL_FLOAT : GL_UNSIGNED_BYTE;
	if (channels == 1)
	{
		// Grey
		internalFormat = (hdr) ? GL_R32F : GL_R8;
		format = GL_RED;
		
		GLint swizzleMask[] = {GL_RED, GL_RED, GL_RED, GL_ONE};
		glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_RGBA, swizzleMask);
	}
	else if (channels == 2)
	{
		// Grey, alpha
		internalFormat = (hdr) ? GL_RG32F : GL_RG8;
		format = GL_RG;
		
		GLint swizzleMask[] = {GL_RED, GL_RED, GL_RED, GL_GREEN};
		glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_RGBA, swizzleMask);
	}
	else if (channels == 3)
	{
		// Red, green, blue
		internalFormat = (hdr) ? GL_RGB32F : GL_RGB8;
		format = GL_RGB;
		
		GLint swizzleMask[] = {GL_RED, GL_GREEN, GL_BLUE, GL_ONE};
		glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_RGBA, swizzleMask);
	}
	else if (channels == 4)
	{
		// Red, green, blue, alpha
		internalFormat = (hdr) ? GL_RGBA32F : GL_RGBA8;
		format = GL_RGBA;
	}
	else
	{
		std::cerr << "TextureLoader::loadMipmap(): Invalid number of color channels in image file \"" << filename << "\"" << std::endl;
		stbi_image_free(pixels);
		return false;
	}
	
	// Upload image data to OpenGL
	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, mipmapLevel, internalFormat, width, height, 0, format, type, pixels);
	
	// Free loaded image data
	stbi_image_free(pixels);
	
	return true;
}

bool TextureLoader::loadCubemapMipmap(Texture* texture, const std::string& filename, int mipmapLevel)
{
	int cubemapWidth;
	int cubemapHeight;
	int channels;
	
	// Determine if image is in an HDR format
	bool hdr = (stbi_is_hdr(filename.c_str()) != 0);
	
	// Disable vertical flip on load
	stbi_set_flip_vertically_on_load(true);
	
	// Load image data
	void* cubemapPixels = nullptr;
	if (hdr)
	{
		cubemapPixels = stbi_loadf(filename.c_str(), &cubemapWidth, &cubemapHeight, &channels, 0);
	}
	else
	{
		cubemapPixels = stbi_load(filename.c_str(), &cubemapWidth, &cubemapHeight, &channels, 0);
	}
	
	// Check if image was loaded
	if (!cubemapPixels)
	{
		std::cerr << "TextureLoader::loadCubemapMipmap(): Failed to load mipmap level " << mipmapLevel << " from \"" << filename << "\"" << std::endl;
		return false;
	}
	
	// Determine cubemap layout
	int layoutIndex = -1;
	CubemapLayout layout;
	for (std::size_t i = 0; i < 5; ++i)
	{
		float aspectRatio = (float)cubemapLayoutDimensions[i][0] / (float)cubemapLayoutDimensions[i][1];
		if ((int)(cubemapHeight * aspectRatio) == cubemapWidth)
		{
			layout = static_cast<CubemapLayout>(i);
			layoutIndex = i;
			break;
		}
	}
		
	// Check for valid layout
	if (layoutIndex == -1)
	{
		std::cerr << "TextureLoader::loadCubemapMipmap(): Invalid cubemap layout in image file \"" << filename << "\"" << std::endl;
		stbi_image_free(cubemapPixels);
		return false;
	}
	
	// Calculate cubemap face size
	int faceSize = cubemapWidth / cubemapLayoutDimensions[static_cast<std::size_t>(layout)][0];
	
	// If this is the base-level mipmap, set the texture dimensions
	if (!mipmapLevel)
	{
		texture->setWidth(faceSize);
		texture->setHeight(faceSize);
	}
	else
	{
		// Verify mipmap dimensions
		if (faceSize != texture->getWidth() >> mipmapLevel)
		{
			std::cerr << "TextureLoader::loadCubemapMipmap(): Mipmap level " << mipmapLevel << " loaded from \"" << filename << "\" has incorrect dimensions" << std::endl;
			stbi_image_free(cubemapPixels);
			return false;
		}
	}
	
	// Select texture formats according to number of color channels in the image
	GLint internalFormat;
	GLenum format;
	GLenum type = (hdr) ? GL_FLOAT : GL_UNSIGNED_BYTE;
	if (channels == 1)
	{
		// Grey
		internalFormat = (hdr) ? GL_R32F : GL_R8;
		format = GL_RED;
		
		GLint swizzleMask[] = {GL_RED, GL_RED, GL_RED, GL_ONE};
		glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_RGBA, swizzleMask);
	}
	else if (channels == 2)
	{
		// Grey, alpha
		internalFormat = (hdr) ? GL_RG32F : GL_RG8;
		format = GL_RG;
		
		GLint swizzleMask[] = {GL_RED, GL_RED, GL_RED, GL_GREEN};
		glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_RGBA, swizzleMask);
	}
	else if (channels == 3)
	{
		// Red, green, blue
		internalFormat = (hdr) ? GL_RGB32F : GL_RGB8;
		format = GL_RGB;
		
		GLint swizzleMask[] = {GL_RED, GL_GREEN, GL_BLUE, GL_ONE};
		glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_RGBA, swizzleMask);
	}
	else if (channels == 4)
	{
		// Red, green, blue, alpha
		internalFormat = (hdr) ? GL_RGBA32F : GL_RGBA8;
		format = GL_RGBA;
	}
	else
	{
		std::cerr << "TextureLoader::loadMipmap(): Invalid number of color channels in image file \"" << filename << "\"" << std::endl;
		stbi_image_free(cubemapPixels);
		return false;
	}
	
	// Allocate cubemap face pixels
	void* facePixels = nullptr;
	if (hdr)
	{
		facePixels = new float[faceSize * faceSize * channels];
	}
	else
	{
		facePixels = new unsigned char[faceSize * faceSize * channels];
	}
	
	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	
	for (int faceIndex = 0; faceIndex < 6; ++faceIndex)
	{
		int offsetX = faceSize * cubemapLayoutOffsets[layoutIndex][faceIndex][0];
		int offsetY = faceSize * ((cubemapLayoutDimensions[layoutIndex][1] - 1) - cubemapLayoutOffsets[layoutIndex][faceIndex][1]);
		
		bool flipX = cubemapLayoutFlips[layoutIndex][faceIndex][0];
		bool flipY = cubemapLayoutFlips[layoutIndex][faceIndex][1];
		
		for (int y = 0; y < faceSize; ++y)
		{
			for (int x = 0; x < faceSize; ++x)
			{
				std::size_t facePixelIndex;
				
				int faceX = (flipX) ? (faceSize - 1 - x) : x;
				int faceY = (flipY) ? (faceSize - 1 - y) : y;
				facePixelIndex = (faceY * faceSize + faceX) * channels;
				
				std::size_t cubemapPixelIndex = ((offsetY + y) * cubemapWidth + (offsetX + x)) * channels;
				
				if (hdr)
				{
					for (int c = 0; c < channels; ++c)
					{
						static_cast<float*>(facePixels)[facePixelIndex + c] = static_cast<float*>(cubemapPixels)[cubemapPixelIndex + c];
					}
				}
				else
				{
					for (int c = 0; c < channels; ++c)
					{
						static_cast<unsigned char*>(facePixels)[facePixelIndex + c] = static_cast<unsigned char*>(cubemapPixels)[cubemapPixelIndex + c];
					}
				}
			}
		}
		
		// Upload cubemap face pixels to OpenGL
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + faceIndex, mipmapLevel, internalFormat, faceSize, faceSize, 0, format, type, facePixels);
	}
	
	// Free cubemap face pixels
	if (hdr)
	{
		delete[] static_cast<float*>(facePixels);
	}
	else
	{
		delete[] static_cast<unsigned char*>(facePixels);
	}
	
	// Free loaded image data
	stbi_image_free(cubemapPixels);
	
	return true;
}

bool TextureLoader::loadMipmapChain(Texture* texture, const std::string& filename)
{
	char* baseMipmapFilenameBuffer = new char[filename.length() + 16];
	std::sprintf(baseMipmapFilenameBuffer, filename.c_str(), 0);
	std::string baseMipmapFilename = baseMipmapFilenameBuffer;
	delete[] baseMipmapFilenameBuffer;
	
	// Load base level mipmap first to retrieve image dimensions
	if (cubemap)
	{
		if (!loadCubemapMipmap(texture, baseMipmapFilename, 0))
		{
			std::cerr << "TextureLoader::loadMipmapChain(): Failed to load cubemap mipmap level 0 from \"" << baseMipmapFilename << "\"" << std::endl;
			return false;
		}
	}
	else
	{
		if (!loadMipmap(texture, baseMipmapFilename, 0))
		{
			std::cerr << "TextureLoader::loadMipmapChain(): Failed to load texture mipmap level 0 from \"" << baseMipmapFilename << "\"" << std::endl;
			return false;
		}
	}
	
	// Check that image dimensions are powers of two
	int width = texture->getWidth();
	int height = texture->getHeight();
	if (width == 0 || (width & (width - 1)) != 0 ||
		height == 0 || (height & (height - 1)) != 0)
	{
		std::cerr << "TextureLoader::loadMipmapChain(): Texture \"" << baseMipmapFilename << "\" has non power-of-two dimensions" << std::endl;
		return false;
	}
	
	// Calculate number of mipmap levels
	int mipmapLevelCount = 1 + std::floor(std::log2(std::max(width, height)));
	
	// Load remaining mipmap levels
	for (int i = 1; i < mipmapLevelCount; ++i)
	{
		char* mipmapFilenameBuffer = new char[filename.length() + 16];
		std::sprintf(mipmapFilenameBuffer, filename.c_str(), i);
		std::string mipmapFilename = mipmapFilenameBuffer;
		delete[] mipmapFilenameBuffer;
		
		if (cubemap)
		{
			if (!loadCubemapMipmap(texture, mipmapFilename, i))
			{
				std::cerr << "TextureLoader::loadMipmapChain(): Failed to load cubemap mipmap level " << i << " from \"" << mipmapFilename << "\"" << std::endl;
				return false;
			}
		}
		else
		{
			if (!loadMipmap(texture, mipmapFilename, i))
			{
				std::cerr << "TextureLoader::loadMipmapChain(): Failed to load texture mipmap level " << i << " from \"" << mipmapFilename << "\"" << std::endl;
				return false;
			}
		}
	}
	
	return true;
}

} // namespace Emergent
