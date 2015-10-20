/*
 * Moveable2D.cpp
 *
 *  Created on: Oct 19, 2015
 *      Author: jusabiaga
 */

#include <cmath>	// cosf, sinf
#include "Defs.hpp"	// f32

#include "Moveable2D.hpp"

namespace JU
{

Moveable2D::Moveable2D(glm::f32 pos_x, glm::f32 pos_y, glm::f32 angle)
		: position_(pos_x, pos_y), angle_(angle)
{
}


void Moveable2D::getToParentTransformation(glm::mat3& to_parent) const
{
	JU::f32 cosine = std::cos(angle_);
	JU::f32 sine   = std::sin(angle_);

	to_parent[0][0] = cosine; to_parent[0][1] = -sine;  to_parent[0][2] = position_[0];
	to_parent[1][0] = sine;   to_parent[1][1] = cosine; to_parent[1][2] = position_[1];
	to_parent[2][0] = 0.0f;   to_parent[2][1] = 0.0f;   to_parent[2][2] = 1.0f;
}



void Moveable2D::getFromParentTransformation(glm::mat3& from_parent) const
{
	JU::f32 cosine = std::cos(angle_);
	JU::f32 sine   = std::sin(angle_);

	from_parent[0][0] = cosine; from_parent[0][1] = sine;  	from_parent[0][2] = -position_[0] * cosine - position_[1] * sine;
	from_parent[1][0] = -sine;  from_parent[1][1] = cosine; from_parent[1][2] =  position_[0] * sine   - position_[1] * cosine;
	from_parent[2][0] = 0.0f;   from_parent[2][1] = 0.0f;   from_parent[2][2] = 1.0f;
}


} /* namespace JU */
