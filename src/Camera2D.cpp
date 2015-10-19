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


Camera2D::Camera2D(Moveable2D moveable, JU::uint32 width, JU::uint32 height)
			: moveable_(moveable), width_(width), height_(height)
{
}


void Camera2D::setMoveable(Moveable2D moveable)
{
	moveable_ = moveable;
}


} /* namespace JU */
