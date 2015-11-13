/*
 * RigidBody.cpp
 *
 *  Created on: Oct 29, 2015
 *      Author: jusabiaga
 */

#include "RigidBody.hpp"
#include "../core/Moveable2D.hpp"		// Moveable2D
#include "../core/Singleton.hpp"        // Singleton
#include "../core/ResourceManager.hpp"  // ResourceManager, Shareable
namespace JU
{

RigidBody::RigidBody(Shareable<BoundingCircle>* pshare_boundingbox, Moveable2D* pmoveable)
                : pshare_boundingbox_(pshare_boundingbox), pmoveable_(pmoveable)
{
}


RigidBody::~RigidBody()
{
    if (pshare_boundingbox_)
        Singleton<ResourceManager<BoundingCircle>>::getInstance()->releaseResource(pshare_boundingbox_);
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
    return pshare_boundingbox_->pdata_;
}



} /* namespace JU */
