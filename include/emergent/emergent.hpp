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

#ifndef EMERGENT_HPP
#define EMERGENT_HPP

#include <emergent/configuration.hpp>
 
 /**
 * @defgroup behavior Behavior
 *
 * Behavior tree nodes
 */
#include <emergent/behavior/action-node.hpp>
#include <emergent/behavior/composite-node.hpp>
#include <emergent/behavior/conditional-node.hpp>
#include <emergent/behavior/counter-node.hpp>
#include <emergent/behavior/decorator-node.hpp>
#include <emergent/behavior/exit-status.hpp>
#include <emergent/behavior/inverter-node.hpp>
#include <emergent/behavior/loop-node.hpp>
#include <emergent/behavior/node.hpp>
#include <emergent/behavior/parallel-node.hpp>
#include <emergent/behavior/selector-node.hpp>
#include <emergent/behavior/sequence-node.hpp>
#include <emergent/behavior/timer-node.hpp>

/**
 * @defgroup entity Entity
 *
 * Entity-component-system (ECS) pattern implementation
 */
#include <emergent/entity/component.hpp>
#include <emergent/entity/component-manager.hpp>
#include <emergent/entity/component-observer.hpp>
#include <emergent/entity/entity-context.hpp>
#include <emergent/entity/entity-id.hpp>
#include <emergent/entity/entity-id-pool.hpp>
#include <emergent/entity/entity-manager.hpp>

/**
 * @defgroup geometry Geometry
 *
 * Computational geometry
 */
#include <emergent/geometry/aabb.hpp>
#include <emergent/geometry/bounding-volume.hpp>
#include <emergent/geometry/convex-hull.hpp>
#include <emergent/geometry/octree.hpp>
#include <emergent/geometry/plane.hpp>
#include <emergent/geometry/ray.hpp>
#include <emergent/geometry/rect.hpp>
#include <emergent/geometry/sphere.hpp>
#include <emergent/geometry/view-frustum.hpp>
#include <emergent/geometry/split-view-frustum.hpp>
#include <emergent/geometry/winged-edge.hpp>

/**
 * @defgroup graphics Graphics
 *
 * High-level hardware-accelerated 3D graphics
 */
#include <emergent/graphics/ambient-light.hpp>
#include <emergent/graphics/animation.hpp>
#include <emergent/graphics/animation-channel.hpp>
#include <emergent/graphics/billboard.hpp>
#include <emergent/graphics/bind-pose.hpp>
#include <emergent/graphics/bone.hpp>
#include <emergent/graphics/camera.hpp>
#include <emergent/graphics/gl3w.hpp>
#include <emergent/graphics/key-frame.hpp>
#include <emergent/graphics/light.hpp>
#include <emergent/graphics/material.hpp>
#include <emergent/graphics/model.hpp>
#include <emergent/graphics/model-instance.hpp>
#include <emergent/graphics/pose.hpp>
#include <emergent/graphics/renderer.hpp>
#include <emergent/graphics/scene-layer.hpp>
#include <emergent/graphics/scene-object.hpp>
#include <emergent/graphics/scene.hpp>
#include <emergent/graphics/shader.hpp>
#include <emergent/graphics/shader-input.hpp>
#include <emergent/graphics/shader-variable.hpp>
#include <emergent/graphics/skeleton.hpp>
#include <emergent/graphics/stb-image.hpp>
#include <emergent/graphics/texture-2d.hpp>
#include <emergent/graphics/texture-cube.hpp>
#include <emergent/graphics/texture-loader.hpp>
#include <emergent/graphics/vertex-format.hpp>

/**
 * @defgroup input Input
 *
 * Input devices and events
 */
#include <emergent/input/arcball.hpp>
#include <emergent/input/control-profile.hpp>
#include <emergent/input/control.hpp>
#include <emergent/input/gamepad.hpp>
#include <emergent/input/input-device.hpp>
#include <emergent/input/input-event.hpp>
#include <emergent/input/input-manager.hpp>
#include <emergent/input/keyboard.hpp>
#include <emergent/input/mouse.hpp>
#include <emergent/input/observers.hpp>
#include <emergent/input/scancode.hpp>

/**
 * @defgroup math Math
 *
 * Essential math functions and structures
 */
#include <emergent/math/glm.hpp>
#include <emergent/math/hash.hpp>
#include <emergent/math/interpolation.hpp>
#include <emergent/math/math.hpp>
#include <emergent/math/transform.hpp>
#include <emergent/math/types.hpp>

/**
 * @defgroup utility Utility
 *
 * Utility classes
 */
#include <emergent/utility/frame-timer.hpp>
#include <emergent/utility/step-interpolator.hpp>
#include <emergent/utility/timer.hpp>
#include <emergent/utility/tween.hpp>

/**
 * @defgroup font Font
 *
 * Font-related classes
 */
#include <emergent/font/font.hpp>
#include <emergent/font/font-loader.hpp>
#include <emergent/font/font-metrics.hpp>
#include <emergent/font/glyph.hpp>
#include <emergent/font/glyph-metrics.hpp>
#include <emergent/font/kerning-table.hpp>
#include <emergent/font/texture-atlas.hpp>
#include <emergent/font/unicode-range.hpp>

/**
 * @defgroup window Window
 *
 * Window management classes
 */
#include <emergent/window/display.hpp>
#include <emergent/window/window-manager.hpp>
#include <emergent/window/window.hpp>

#endif // EMERGENT_HPP

