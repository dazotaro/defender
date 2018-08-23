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

/**
 * Default constructor
 */
GameObject::GameObject() : pmesh_instance_(nullptr),
                           prigid_body_(nullptr),
                           collideable_(false)
{
}


/**
 * Non-default constructor
 *
 * @param name 				Name of the object
 * @param pmesh_instance	Address of the mesh instance
 * @param moveable			Moveable object
 * @param prigid_body		Address of the rigid body
 * @param collideable		Collideable object
 */
GameObject::GameObject(const std::string& name,
                       GLMesh2DInstance* pmesh_instance,
                       Moveable2D        moveable,
                       RigidBody*        prigid_body,
                       bool              collideable)
               :    name_(name),
                    pmesh_instance_(pmesh_instance),
                    moveable_(moveable),
                    prigid_body_(prigid_body),
                    collideable_(collideable)
{
}


/**
 * Destructor
 */
GameObject::~GameObject()
{
    delete pmesh_instance_;
    delete prigid_body_;
}


/**
 * Get name
 *
 * @return Name
 */
const std::string& GameObject::getName() const
{
    return name_;
}


/**
 * Set name
 *
 * @param name Name string
 */
void GameObject::setName(const std::string& name)
{
    name_ = name;
}


/**
 * Get mesh instance
 *
 * @return Address of mesh instance
 */
const GLMesh2DInstance* GameObject::getMeshInstance() const
{
    return pmesh_instance_;
}


/**
 * Return moveable object
 *
 * @return Moveable object
 */
const Moveable2D& GameObject::getMoveable() const
{
    return moveable_;
}


/**
 * Return moveable object
 *
 * @return Moveable object
 */
Moveable2D& GameObject::getMoveable()
{
    return moveable_;
}


/**
 * Set mesh instance
 *
 * @param pmesh_instance Address of mesh instance
 */
void GameObject::setMeshInstance(GLMesh2DInstance* pmesh_instance)
{
    pmesh_instance_ = pmesh_instance;
}


/**
 * Set moveable object
 *
 * @param moveable Moveable object
 */
void GameObject::setMoveable2D(Moveable2D moveable)
{
    moveable_ = moveable;
}


/**
 * Set rigid object
 *
 * @param prigid_body Address of rigid body
 */
void GameObject::setRigidBody(RigidBody* prigid_body)
{
    prigid_body_ = prigid_body;
    prigid_body_->setMoveable(&moveable_);
}


/**
 * Set collideable object
 *
 * @param collideable Collideable object
 */
void GameObject::setCollideable(bool collideable)
{
    collideable_ = collideable;
}


/**
 * Get rigid object
 *
 * @return Address of rigid object
 */
RigidBody* GameObject::getRigidBody() const
{
    return prigid_body_;
}


/**
 * Render game object
 *
 * @param program GLSL program
 * @param model	  Model matrix (homogeneous)
 * @param view	  View matrix (homogeneous)
 */
void GameObject::render(const GLSLProgram &program, const glm::mat3 & model, const glm::mat3 &view) const
{
}

} /* namespace JU */
