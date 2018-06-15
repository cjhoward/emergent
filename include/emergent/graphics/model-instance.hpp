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

#ifndef EMERGENT_GRAPHICS_MODEL_INSTANCE_HPP
#define EMERGENT_GRAPHICS_MODEL_INSTANCE_HPP

#include <emergent/graphics/scene-object.hpp>

namespace Emergent
{

class Model;
class Pose;

/**
 * An instance of a 3D model.
 *
 * @ingroup graphics
 */
class ModelInstance: public SceneObject
{
public:
	ModelInstance(const Model* model);
	ModelInstance();
	
	void setModel(const Model* model);
	void setPose(Pose* pose);
	
	virtual SceneObjectType getSceneObjectType() const;
	const Model* getModel() const;
	
	const Pose* getPose() const;
	Pose* getPose();
	
private:
	virtual AABB calculateBounds() const;
	
	const Model* model;
	Pose* pose;
};

inline void ModelInstance::setPose(Pose* pose)
{
	this->pose = pose;
}

inline SceneObjectType ModelInstance::getSceneObjectType() const
{
	return SceneObjectType::MODEL_INSTANCE;
}

inline const Model* ModelInstance::getModel() const
{
	return model;
}

inline const Pose* ModelInstance::getPose() const
{
	return pose;
}

inline Pose* ModelInstance::getPose()
{
	return pose;
}

} // namespace Emergent

#endif // EMERGENT_GRAPHICS_MODEL_INSTANCE_HPP
