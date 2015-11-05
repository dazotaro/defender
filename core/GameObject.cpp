/*
 * GameObject.cpp
 *
 *  Created on: Oct 21, 2015
 *      Author: jusabiaga
 */

#include "GameObject.hpp"
#include "../graphics/GLMesh2DInstance.hpp"     // JU::GLMesh2DInstance
#include "../graphics/GLSLProgram.hpp"          // JU::GLSLProgram
#include "../physics/RigidBody.hpp" // JU::RigidBody

namespace JU
{

GameObject::GameObject() : pmesh_instance_(nullptr),
                           prigid_body_(nullptr),
                           collideable_(false)
{
}


GameObject::GameObject(GLMesh2DInstance* pmesh_instance,
                       Moveable2D        moveable,
                       RigidBody*        prigid_body,
                       bool              collideable)
                           : pmesh_instance_(pmesh_instance),
                             moveable_(moveable),
                             prigid_body_(prigid_body),
                             collideable_(collideable)
{
}


GameObject::~GameObject()
{
    delete pmesh_instance_;
    delete prigid_body_;
}


const GLMesh2DInstance* GameObject::getMeshInstance() const
{
    return pmesh_instance_;
}


const Moveable2D& GameObject::getMoveable() const
{
    return moveable_;
}


Moveable2D& GameObject::getMoveable()
{
    return moveable_;
}


void GameObject::setMeshInstance(GLMesh2DInstance* pmesh_instance)
{
    pmesh_instance_ = pmesh_instance;
}


void GameObject::setMoveable2D(Moveable2D moveable)
{
    moveable_ = moveable;
}


void GameObject::setRigitBody(RigidBody* prigid_body)
{
    prigid_body_ = prigid_body;
    prigid_body_->setMoveable(&moveable_);
}


void GameObject::setCollideable(bool collideable)
{
    collideable_ = collideable;
}


RigidBody* GameObject::getRigidBody() const
{
    return prigid_body_;
}



void GameObject::render(const GLSLProgram &program, const glm::mat3 & model, const glm::mat3 &view) const
{
}

} /* namespace JU */
