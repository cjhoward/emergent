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

#include <emergent/font/texture-packer.hpp>

namespace Emergent
{

TexturePackerNode* TexturePackerNode::insert(float width, float height)
{
	// If not a leaf node
	if (children[0] && children[1])
	{
		// Insert into first child
		TexturePackerNode* node = children[0]->insert(width, height);
		if (node)
		{
			return node;
		}
		
		// First child full, insert into second
		return children[1]->insert(width, height);
	}
	
	// Check if texture already exists
	if (reserved)
	{
		return nullptr;
	}
	
	float boundsWidth = bounds.getWidth();
	float boundsHeight = bounds.getHeight();
	
	// Check if area cannot accommodate texture
	if (width > boundsWidth || height > boundsHeight)
	{
		return nullptr;
	}
	
	// Check for a perfect fit.
	if (width == boundsWidth && height == boundsHeight)
	{
		return this;
	}
	
	// Split node
	children[0] = new TexturePackerNode();
	children[1] = new TexturePackerNode();
	
	// Determine split direction
	float dw = boundsWidth - width;
	float dh = boundsHeight - height;
	
	if (dw > dh)
	{
		children[0]->bounds.setMin(bounds.getMin());
		children[0]->bounds.setMax(Vector2(bounds.getMin()[0] + width, bounds.getMax()[1]));
			
		children[1]->bounds.setMin(Vector2(bounds.getMin()[0] + width, bounds.getMin()[1]));
		children[1]->bounds.setMax(bounds.getMax());
	}
	else
	{		
		children[0]->bounds.setMin(bounds.getMin());
		children[0]->bounds.setMax(Vector2(bounds.getMax()[0], bounds.getMin()[1] + height));
			
		children[1]->bounds.setMin(Vector2(bounds.getMin()[0], bounds.getMin()[1] + height));
		children[1]->bounds.setMax(bounds.getMax());
	}
	
	return children[0]->insert(width, height);
}

TexturePacker::TexturePacker(const Rect& bounds)
{
	root.bounds = bounds;
}

TexturePacker::~TexturePacker()
{}

const TexturePackerNode* TexturePacker::pack(float width, float height)
{
	TexturePackerNode* node = root.insert(width, height);
	if (node)
	{
		node->reserved = true;
	}
	
	return node;
}

void TexturePacker::clear()
{
	delete root.children[0];
	delete root.children[1];
	root.children[0] = root.children[1] = nullptr;
}

} // namespace Emergent
