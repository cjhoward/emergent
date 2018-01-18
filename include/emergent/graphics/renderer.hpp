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

#ifndef EMERGENT_GRAPHICS_RENDERER_HPP
#define EMERGENT_GRAPHICS_RENDERER_HPP

#include <emergent/graphics/gl3w.hpp>
#include <emergent/graphics/shader.hpp>
#include <emergent/math/types.hpp>
#include <list>
#include <map>

namespace Emergent
{

class Camera;
class Scene;
class SceneLayer;
class Material;
class Pose;
class SceneObject;
class ModelInstance;
class BillboardBatch;

/*
1. Scene containing objects (cameras, lights, geometry) is passed to Renderer::render()
2. Renderer gathers active cameras and forms the lighting state
3. For each camera, the scene is queried for visibile geometry
4. Visibile geometry is sorted into a render queue of render operations
5. For each render pass of the camera, render operations are passed to RenderPass::render()
(Steps 6 and 7 may vary for post-processng passes, which simply use a fullscreen quad)
6. For each render operation, a hash value is calculated and used to retrieve the required shader
7. Shader parameters are passed and the geometry is rendered to the render pass's render target
*/

/**
 * A framebuffer which can be rendered to.
 *
 * @ingroup graphics
 */
struct RenderTarget
{
	GLuint framebuffer;
	int width;
	int height;
};

/**
 * All information required to render a single piece of geometry.
 *
 * @ingroup graphics
 */
struct RenderOperation
{
	GLuint vao;
	std::size_t indexOffset;
	std::size_t triangleCount;
	const Material* material;
	glm::mat4 transform;
	const Pose* pose;
	float depth;
};

/**
 * A list of objects which should be rendered.
 *
 * @ingroup graphics
 */
class RenderQueue
{
public:
	void queue(const SceneObject* object);
	void queue(const ModelInstance* instance);
	void queue(const BillboardBatch* batch);	
	void queue(const RenderOperation& op);
	
	/**
	 * Sorts operations in the render queue according to the specified comparison function object.
	 *
	 * @param compare Comparison function object.
	 */
	template <typename T>
	void sort(T compare);
	
	/**
	 * Removes all operations from the render queue.
	 */
	void clear();
	
	const std::list<RenderOperation>* getOperations() const;
	
	std::list<RenderOperation>* getOperations();

private:
	std::list<RenderOperation> operations;
};

template <typename T>
void RenderQueue::sort(T compare)
{
	operations.sort(compare);
}

inline const std::list<RenderOperation>* RenderQueue::getOperations() const
{
	return &operations;
}

inline std::list<RenderOperation>* RenderQueue::getOperations()
{
	return &operations;
}

/**
 * Information required by a render pass.
 *
 * @ingroup graphics
 */
struct RenderContext
{
public:
	/// Pointer to the active camera
	const Camera* camera;
	
	/// Pointer to the active scene layer
	const SceneLayer* layer;
	
	/// Pointer to the loaded render queue
	RenderQueue* queue;
};

/**
 * A single render pass.
 *
 * @ingroup graphics
 */
class RenderPass
{
public:
	RenderPass();
	virtual ~RenderPass();
	
	/// Loads data required by the render pass. The render context should contain all possible types of objects which can be rendered, to ensure that all necessary shaders are loaded.
	virtual bool load(const RenderContext* renderContext) = 0;
	
	/// Unloads all loaded data.
	virtual void unload() = 0;
	
	/// Performs a single render pass, given a render context.
	virtual void render(RenderContext* renderContext) = 0;
	
	/// Enables or disales the render pass.
	void setEnabled(bool enabled);
	
	/// Sets the target of this render pass.
	void setRenderTarget(const RenderTarget* target);
	
	/// Returns `true` if the render pass is enabled.
	bool isEnabled() const;
	
protected:
	const RenderTarget* renderTarget;
	
private:
	bool enabled;
};

inline void RenderPass::setEnabled(bool enabled)
{
	this->enabled = enabled;
}

inline void RenderPass::setRenderTarget(const RenderTarget* target)
{
	this->renderTarget = target;
}

inline bool RenderPass::isEnabled() const
{
	return enabled;
}

/**
 * Contains a list of render passes which can be sequentially processed in order to produce a final composite image.
 *
 * @ingroup graphics
 */
class Compositor
{
public:
	/// Sequentially loads each render pass.
	bool load(const RenderContext* renderContext);
	
	/// Sequentially unloads each render pass.
	void unload();
	
	/// Sequentially renders each render pass.
	void render(RenderContext* renderContext);
	
	/// Adds a pass to the compositor.
	void addPass(RenderPass* pass);
	
	/// Removes all passes from the compositor.
	void removePasses();

	/// Returns the number of render passes in the compositer.
	std::size_t getPassCount() const;
	
	/// Returns the render pass at the specified index.
	const RenderPass* getPass(std::size_t index) const;
	
	/// @copydoc Compositor::getPass() const
	RenderPass* getPass(std::size_t index);
	
private:
	std::vector<RenderPass*> passes;
};

inline void Compositor::addPass(RenderPass* pass)
{
	passes.push_back(pass);
}

inline void Compositor::removePasses()
{
	passes.clear();
}

inline std::size_t Compositor::getPassCount() const
{
	return passes.size();
}

inline const RenderPass* Compositor::getPass(std::size_t index) const
{
	return passes[index];
}

inline RenderPass* Compositor::getPass(std::size_t index)
{
	return passes[index];
}

/**
 * Renders scenes using their respective cameras.
 *
 * @ingroup graphics
 */
class Renderer
{
public:
	Renderer();
	~Renderer();
	
	void render(const Scene& scene);
	
private:
	RenderQueue renderQueue;
	RenderContext renderContext;
};

} // namespace Emergent

#endif // EMERGENT_GRAPHICS_RENDERER_HPP
