/*
 * Camera2D.cpp
 *
 *  Created on: Oct 19, 2015
 *      Author: jusabiaga
 */

#include "Camera2D.hpp"

namespace JU
{

Camera2D::Camera2D() : width_(0), height_(0)
{
}


Camera2D::Camera2D(Moveable2D moveable, JU::uint32 width, JU::uint32 height)
			: moveable_(moveable), width_(width), height_(height)
{
}


void Camera2D::setMoveable(Moveable2D moveable)
{
	moveable_ = moveable;
}


void Camera2D::getWorld2NDCTransformation(glm::mat3& view) const
{
	moveable_.getFromParentTransformation(view);

	glm::mat3 scale(1.0f / width_,          0.0f,  0.0f,
    						 0.0f, 1.0 / height_,  0.0f,
							 0.0f,          0.0f,  1.0f);
	view = scale * view;
}


} /* namespace JU */
