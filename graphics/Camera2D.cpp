/*
 * Camera2D.cpp
 *
 *  Created on: Oct 19, 2015
 *      Author: jusabiaga
 */

#include "Camera2D.hpp"

namespace JU
{

/**
 * Default constructor
 */
Camera2D::Camera2D()
{
}


/**
 * Non-default constructor
 *
 * @param moveable 2D rotation and translation
 */
Camera2D::Camera2D(Moveable2D moveable) : moveable_(moveable)
{
}


/**
 * Get moveable object
 *
 * @return Moveable object (rotation and translation)
 */
const Moveable2D& Camera2D::getMoveable() const
{
    return moveable_;
}


/**
 * Get moveable object
 *
 * @return Moveable object (rotation and translation)
 */
Moveable2D& Camera2D::getMoveable()
{
    return moveable_;
}


/**
 * Set moveable object
 *
 * @param moveable Rotation and translation
 */
void Camera2D::setMoveable(Moveable2D moveable)
{
    moveable_ = moveable;
}


/**
 * Get World to NDC (homogeneous) transformation matrix
 *
 * @param (output) World to NDC (homogeneous) matrix
 */
void Camera2D::getWorld2NDCTransformation(glm::mat3& view) const
{
    moveable_.getFromParentTransformation(view);
}


} /* namespace JU */
