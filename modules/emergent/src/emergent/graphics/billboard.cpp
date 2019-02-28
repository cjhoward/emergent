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

#include <emergent/graphics/billboard.hpp>
#include <emergent/graphics/vertex-format.hpp>
#include <emergent/graphics/camera.hpp>
#include <emergent/math/interpolation.hpp>
#include <emergent/math/math.hpp>

namespace Emergent
{

Billboard::Billboard():
	translation(0.0f),
	rotation(1.0, 0.0f, 0.0f, 0.0f),
	dimensions(1.0f),
	coordinatesMin(0.0f),
	coordinatesMax(1.0f),
	tintColor(1.0f),
	translationTween(&translation, lerp<Vector3>),
	rotationTween(&rotation, slerp<Quaternion>),
	dimensionsTween(&dimensions, lerp<Vector2>),
	coordinatesMinTween(&coordinatesMin, lerp<Vector2>),
	coordinatesMaxTween(&coordinatesMax, lerp<Vector2>),
	tintColorTween(&tintColor, lerp<Vector4>)
{}

void Billboard::resetTweens()
{
	translationTween.reset();
	rotationTween.reset();
	dimensionsTween.reset();
	coordinatesMinTween.reset();
	coordinatesMaxTween.reset();
	tintColorTween.reset();
}

BillboardBatch::Range::Range():
	material(nullptr),
	start(0),
	length(0)
{}

BillboardBatch::Range::Range(const BillboardBatch::Range& range):
	material(range.material),
	start(range.start),
	length(range.length)
{}

BillboardBatch::BillboardBatch():
	vertexSize(0),
	vertexCount(0),
	vertexData(nullptr),
	indexCount(0),
	triangleCount(0),
	camera(nullptr),
	alignmentMode(BillboardAlignmentMode::SPHERICAL),
	alignmentVector(0, 1, 0)
{}

BillboardBatch::~BillboardBatch()
{
	if (!billboards.empty())
	{
		delete[] vertexData;
		vertexData = nullptr;
		
		glDeleteBuffers(1, &ibo);
    	glDeleteBuffers(1, &vbo);
    	glDeleteVertexArrays(1, &vao);
	}
}

BillboardBatch::Range* BillboardBatch::addRange()
{
	ranges.push_back(Range());
	return &ranges.back();
}

void BillboardBatch::removeRanges()
{
	ranges.clear();
}

void BillboardBatch::setAlignment(const Camera* camera, BillboardAlignmentMode mode)
{
	this->camera = camera;
	this->alignmentMode = mode;
}

void BillboardBatch::setAlignmentVector(const Vector3& direction)
{
	this->alignmentVector = direction;
}

void BillboardBatch::resize(std::size_t count)
{
	if (!billboards.empty())
	{
		delete[] vertexData;
		vertexData = nullptr;
		
		glDeleteBuffers(1, &ibo);
    	glDeleteBuffers(1, &vbo);
    	glDeleteVertexArrays(1, &vao);
	}
	
	// Allocate billboards
	billboards.resize(count);
	
	// Create VAO
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	// Generate VBO
	vertexSize = 3 + 4 + 2;
	vertexCount = billboards.size() * 4;
	vertexData = new float[vertexCount * vertexSize];
	indexCount = billboards.size() * 6;
	triangleCount = billboards.size() * 2;
	
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexSize * vertexCount, nullptr, GL_DYNAMIC_DRAW);
	
	// Setup vertex attribute array
	glEnableVertexAttribArray(EMERGENT_VERTEX_POSITION);
	glVertexAttribPointer(EMERGENT_VERTEX_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(float) * vertexSize, (char*)0 + 0 * sizeof(GLfloat));
	glEnableVertexAttribArray(EMERGENT_VERTEX_COLOR);
	glVertexAttribPointer(EMERGENT_VERTEX_COLOR, 4, GL_FLOAT, GL_FALSE, sizeof(float) * vertexSize, (char*)0 + 3 * sizeof(GLfloat));
	glEnableVertexAttribArray(EMERGENT_VERTEX_TEXCOORD);
	glVertexAttribPointer(EMERGENT_VERTEX_TEXCOORD, 2, GL_FLOAT, GL_FALSE, sizeof(float) * vertexSize, (char*)0 + 7 * sizeof(GLfloat));
	
	// Generate IBO and upload data
	std::uint32_t* indexData32 = new std::uint32_t[indexCount];
	std::uint32_t* index = &indexData32[0];
	for (std::size_t i = 0; i < billboards.size(); ++i)
	{
		std::size_t vertex0 = i * 4;
		
		*(index++) = vertex0 + 0;
		*(index++) = vertex0 + 2;
		*(index++) = vertex0 + 1;
		*(index++) = vertex0 + 0;
		*(index++) = vertex0 + 3;
		*(index++) = vertex0 + 2;
	}
	
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(std::uint32_t) * indexCount, indexData32, GL_STATIC_DRAW);
	
	delete[] indexData32;
}

void BillboardBatch::interpolate(float a)
{
	for (Billboard& billboard: billboards)
	{
		billboard.getTranslationTween()->interpolate(a);
		billboard.getRotationTween()->interpolate(a);
		billboard.getDimensionsTween()->interpolate(a);
		billboard.getTextureCoordinatesMinTween()->interpolate(a);
		billboard.getTextureCoordinatesMaxTween()->interpolate(a);
		billboard.getTintColorTween()->interpolate(a);
	}
}

void BillboardBatch::reset()
{
	for (Billboard& billboard: billboards)
	{
		billboard.getTranslationTween()->reset();
		billboard.getRotationTween()->reset();
		billboard.getDimensionsTween()->reset();
		billboard.getTextureCoordinatesMinTween()->reset();
		billboard.getTextureCoordinatesMaxTween()->reset();
		billboard.getTintColorTween()->reset();
	}
}

void BillboardBatch::batch()
{
	Quaternion alignment(1, 0, 0, 0);
	
	float* v = &vertexData[0];
	for (std::size_t i = 0; i < billboards.size(); ++i)
	{
		const Billboard& billboard = billboards[i];
		const Vector3& translation = billboard.getTranslationTween()->getSubstate();
		const Quaternion& rotation = billboard.getRotationTween()->getSubstate();
		const Vector2& dimensions = billboard.getDimensionsTween()->getSubstate();
		const Vector2& coordinatesMin = billboard.getTextureCoordinatesMinTween()->getSubstate();
		const Vector2& coordinatesMax = billboard.getTextureCoordinatesMaxTween()->getSubstate();
		const Vector4& tintColor = billboard.getTintColorTween()->getSubstate();
		Vector2 uv(0.0f);
		
		if (camera != nullptr)
		{
			if (alignmentMode == BillboardAlignmentMode::SPHERICAL)
			{
				alignment = glm::normalize(rotation * lookRotation(-camera->getForwardTween()->getSubstate(), -camera->getUpTween()->getSubstate()));
			}
			else if (alignmentMode == BillboardAlignmentMode::CYLINDRICAL)
			{
				Vector3 look = glm::normalize(projectOnPlane((translation - camera->getTransformTween()->getSubstate().translation), Vector3(0.0f), rotation * alignmentVector));
				Vector3 up = glm::normalize(rotation * getUpTween()->getSubstate());
				alignment = glm::normalize(lookRotation(look, up));
			}
		}
		else
		{
			alignment = rotation;
		}
				
		Vector2 offset = dimensions * 0.5f;
		Vector3 v0 = translation + alignment * Vector3(-offset.x, -offset.y, 0.0f);
		Vector3 v1 = translation + alignment * Vector3(offset.x, -offset.y, 0.0f);
		Vector3 v2 = translation + alignment * Vector3(offset.x, offset.y, 0.0f);
		Vector3 v3 = translation + alignment * Vector3(-offset.x, offset.y, 0.0f);
		
		*(v++) = v0.x;
		*(v++) = v0.y;
		*(v++) = v0.z;
		*(v++) = tintColor.r;
		*(v++) = tintColor.g;
		*(v++) = tintColor.b;
		*(v++) = tintColor.a;
		*(v++) = coordinatesMin.x;
		*(v++) = coordinatesMax.y;
		
		*(v++) = v1.x;
		*(v++) = v1.y;
		*(v++) = v1.z;
		*(v++) = tintColor.r;
		*(v++) = tintColor.g;
		*(v++) = tintColor.b;
		*(v++) = tintColor.a;
		*(v++) = coordinatesMax.x;
		*(v++) = coordinatesMax.y;
		
		*(v++) = v2.x;
		*(v++) = v2.y;
		*(v++) = v2.z;
		*(v++) = tintColor.r;
		*(v++) = tintColor.g;
		*(v++) = tintColor.b;
		*(v++) = tintColor.a;
		*(v++) = coordinatesMax.x;
		*(v++) = coordinatesMin.y;
		
		*(v++) = v3.x;
		*(v++) = v3.y;
		*(v++) = v3.z;
		*(v++) = tintColor.r;
		*(v++) = tintColor.g;
		*(v++) = tintColor.b;
		*(v++) = tintColor.a;
		*(v++) = coordinatesMin.x;
		*(v++) = coordinatesMin.y;
	}
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * vertexSize * vertexCount, vertexData);
}

} // namespace Emergent
