/*
 * RigidBody.cpp
 *
 *  Created on: Oct 29, 2015
 *      Author: jusabiaga
 */

#include "RigidBody.hpp"
#include "../src/Moveable2D.hpp"		// Moveable2D

namespace JU
{


RigidBody::RigidBody(const BoundingCircle* pbounding_area, Moveable2D* pmoveable) : pbounding_area_(pbounding_area), pmoveable_(pmoveable)
{
}

RigidBody::~RigidBody()
{
}


} /* namespace JU */
