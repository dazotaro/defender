/*
 * GameObject.cpp
 *
 *  Created on: Oct 21, 2015
 *      Author: jusabiaga
 */

#include "GameObject.hpp"
#include "GLMesh2DInstance.hpp"		// JU::GLMesh2DInstance
#include "Moveable2D.hpp"			// JU::Moveable2D
#include "GLSLProgram.hpp"			// JU::GLSLProgram

namespace JU
{

GameObject::GameObject() : mesh_instance_(nullptr), moveable_(nullptr)
{
}


GameObject::GameObject(GLMesh2DInstance* mesh_instance, Moveable2D* moveable) : mesh_instance_(mesh_instance), moveable_(moveable)
{
}


GameObject::~GameObject()
{
}


const GLMesh2DInstance* GameObject::getMeshInstance() const
{
	return mesh_instance_;
}


void GameObject::setMeshInstance(GLMesh2DInstance* mesh_instance)
{
	mesh_instance_ = mesh_instance;
}


void GameObject::setMoveable2D(Moveable2D* moveable)
{
	moveable_ = moveable;
}


void GameObject::render(const GLSLProgram &program, const glm::mat3 & model, const glm::mat3 &view) const
{
}

} /* namespace JU */
