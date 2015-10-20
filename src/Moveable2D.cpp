/*
 * Moveable2D.cpp
 *
 *  Created on: Oct 19, 2015
 *      Author: jusabiaga
 */

#include "Moveable2D.hpp"

namespace JU
{

Moveable2D::Moveable2D(glm::f32 pos_x, glm::f32 pos_y, glm::f32 angle)
		: position_(pos_x, pos_y), angle_(angle)
{
}

} /* namespace JU */
