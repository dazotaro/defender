/*
 * Camera2D.cpp
 *
 *  Created on: Oct 19, 2015
 *      Author: jusabiaga
 */

#include "Camera2D.hpp"

namespace JU
{

Camera2D::Camera2D()
{
}


Camera2D::Camera2D(Moveable2D moveable)
            : moveable_(moveable)
{
}


void Camera2D::setMoveable(Moveable2D moveable)
{
    moveable_ = moveable;
}


void Camera2D::getWorld2NDCTransformation(glm::mat3& view) const
{
    moveable_.getFromParentTransformation(view);
}


} /* namespace JU */
