/*
 * RigidBody.cpp
 *
 *  Created on: Oct 29, 2015
 *      Author: jusabiaga
 */

#include "RigidBody.hpp"
#include "../core/Moveable2D.hpp"		// Moveable2D
#include "../core/Singleton.hpp"        // Singleton
#include "../core/ResourceManager.hpp"  // ResourceManager, ShareableResource
namespace JU
{

RigidBody::RigidBody(ShareableResource<BoundingCircle>* pboundingarea_resource, Moveable2D* pmoveable)
                : pboundingarea_resource_(pboundingarea_resource), pmoveable_(pmoveable)
{
}


RigidBody::~RigidBody()
{
    Singleton<ResourceManager<BoundingCircle>>::getInstance()->releaseResource(pboundingarea_resource_);
}


void RigidBody::setMoveable(Moveable2D* pmoveable)
{
    pmoveable_ = pmoveable;
}


const Moveable2D* RigidBody::getMoveable() const
{
    return pmoveable_;
}


const BoundingCircle* RigidBody::getBoundingArea() const
{
    return pboundingarea_resource_->pdata_;
}



} /* namespace JU */
