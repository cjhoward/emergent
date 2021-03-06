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

#include <emergent/graphics/renderer.hpp>
#include <emergent/graphics/camera.hpp>
#include <emergent/graphics/model.hpp>
#include <emergent/graphics/scene.hpp>
#include <emergent/graphics/scene-object.hpp>
#include <emergent/graphics/model-instance.hpp>
#include <emergent/graphics/light.hpp>
#include <emergent/graphics/billboard.hpp>
#include <emergent/graphics/vertex-format.hpp>
#include <iostream>

namespace Emergent
{

void RenderQueue::queue(const SceneObject* object)
{
	if (object->isActive())
	{
		SceneObjectType type = object->getSceneObjectType();
		
		if (type == SceneObjectType::MODEL_INSTANCE)
		{
			queue(static_cast<const ModelInstance*>(object));
		}
		else if (type == SceneObjectType::BILLBOARD_BATCH)
		{
			queue(static_cast<const BillboardBatch*>(object));
		}
	}
}

void RenderQueue::queue(const ModelInstance* instance)
{
	// Create new render operation
	RenderOperation operation;

	// Set operation transform
	operation.transform = instance->getTransformMatrixTween()->getSubstate();
	
	const Model* model = instance->getModel();
	operation.vao = model->getVAO();
	operation.pose = instance->getPose();
	
	for (std::size_t i = 0; i < model->getGroupCount(); ++i)
	{
		// Queue a render operation for each model group
		const Model::Group* group = model->getGroup(i);
		
		operation.indexOffset = group->indexOffset;
		operation.triangleCount = group->triangleCount;

		if (instance->getMaterialSlot(i) != nullptr)
		{
			operation.material = instance->getMaterialSlot(i);
		}
		else
		{
			operation.material = group->material;
		}

		queue(operation);
	}
}

void RenderQueue::queue(const BillboardBatch* batch)
{
	// Create new render operation
	RenderOperation operation;

	// Set operation transform
	operation.transform = batch->getTransformMatrixTween()->getSubstate();
	operation.vao = batch->vao;
	operation.pose = nullptr;
	
	for (std::size_t i = 0; i < batch->getRangeCount(); ++i)
	{
		const BillboardBatch::Range* range = batch->getRange(i);
		operation.material = range->material;
		operation.indexOffset = range->start * 4;
		operation.triangleCount = range->length * 2;
		
		queue(operation);
	}
}

void RenderQueue::queue(const RenderOperation& operation)
{
	operations.push_back(operation);
}

void RenderQueue::clear()
{
	operations.clear();
}

RenderPass::RenderPass():
	renderTarget(nullptr),
	enabled(true)
{}

RenderPass::~RenderPass()
{}

bool Compositor::load(const RenderContext* renderContext)
{
	bool status = true;
	std::size_t index = 0;
	
	for (RenderPass* pass: passes)
	{
		if (!pass->load(renderContext))
		{
			status = false;
			std::cerr << "Compositor failed to load render pass at index " << index << std::endl;
		}
		
		++index;
	}
	
	return status;
}

void Compositor::unload()
{
	for (RenderPass* pass: passes)
	{
		pass->unload();
	}
}

void Compositor::render(RenderContext* renderContext)
{
	for (RenderPass* pass: passes)
	{
		if (pass->isEnabled())
		{
			pass->render(renderContext);
		}
	}
}

Renderer::Renderer()
{}

Renderer::~Renderer()
{}

void Renderer::render(const Scene& scene)
{
	// Gather active cameras
	std::list<Camera*> cameras;
	if (scene.getObjects(SceneObjectType::CAMERA) == nullptr)
	{
		return;
	}
	
	for (auto object: *(scene.getObjects(SceneObjectType::CAMERA)))
	{
		Camera* camera = static_cast<Camera*>(object);
		
		if (camera->isActive())
		{
			cameras.push_back(camera);
		}
	}
	
	// Sort active cameras by their composite indices
	cameras.sort(
		[](const Camera* lhs, const Camera* rhs)
		{
			return lhs->getCompositeIndex() < rhs->getCompositeIndex();
		});
	
	// For each active camera
	for (Camera* camera: cameras)
	{
		const ViewFrustum& viewFrustum = camera->getViewFrustumTween()->getSubstate();

		const std::list<SceneObject*>* objects = scene.getObjects();
		if (objects == nullptr)
		{
			continue;
		}
		
		// Add visible objects to render queue
		for (SceneObject* object: *objects)
		{
			if (camera->isCullingEnabled() && object->isCullingEnabled())
			{
				const BoundingVolume* cameraCullingVolume = &viewFrustum;
				const BoundingVolume* objectCullingVolume = &object->getBoundsTween()->getSubstate();
				if (camera->getCullingMask())
				{
					cameraCullingVolume = camera->getCullingMask();
				}

				if (object->getCullingMask())
				{
					objectCullingVolume = object->getCullingMask();
				}

				// Cull objects outside culling volume
				if (!cameraCullingVolume->intersects(*objectCullingVolume))
				{
					continue;
				}
			}
			
			renderQueue.queue(object);
		}
		
		// Calculate depths (distance to near clipping plane)
		for (RenderOperation& op: *renderQueue.getOperations())
		{
			op.depth = viewFrustum.getNear().distance(Vector3(op.transform[3]));
		}
		
		// Form render context
		renderContext.camera = camera;
		renderContext.scene = &scene;
		renderContext.queue = &renderQueue;
		
		// Pass render context to the camera's compositor and render it
		camera->getCompositor()->render(&renderContext);
		
		// Clear render queue
		renderQueue.clear();
	}
}

} // namespace Emergent
