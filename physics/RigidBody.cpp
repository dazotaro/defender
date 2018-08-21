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


/**
 * Non-default Constructor
 *
 * @param pshare_boundingbox (shareable) bounding box
 * @param pmoveable			 Address of moveable object (rotation and translation)
 */
RigidBody::RigidBody(Shareable<BoundingCircle>* pshare_boundingbox, Moveable2D* pmoveable)
                : pshare_boundingbox_(pshare_boundingbox), pmoveable_(pmoveable)
{
}


/**
 * Destructor
 */
RigidBody::~RigidBody()
{
    if (pshare_boundingbox_)
        Singleton<ResourceManager<BoundingCircle>>::getInstance()->releaseResource(pshare_boundingbox_);
}


/**
 * Set moveable object
 *
 * @param pmoveable Address of moveable object
 */
void RigidBody::setMoveable(Moveable2D* pmoveable)
{
    pmoveable_ = pmoveable;
}


/**
 * Get moveable object
 *
 * @return Address of moveable object
 */
const Moveable2D* RigidBody::getMoveable() const
{
    return pmoveable_;
}


/**
 * Get bounding area
 *
 * @return Address of bounding area ojbect
 */
const BoundingCircle* RigidBody::getBoundingArea() const
{
    return pshare_boundingbox_->pdata_;
}



} /* namespace JU */
