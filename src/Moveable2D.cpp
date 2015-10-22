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

Moveable2D::Moveable2D(glm::f32 posx, glm::f32 posy, glm::f32 angle, glm::f32 scalex, glm::f32 scaley)
		: position_(posx, posy), angle_(angle), scale_(scalex, scaley)
{
}


void Moveable2D::getToParentTransformation(glm::mat3& to_parent) const
{
	JU::f32 cosine = std::cos(angle_);
	JU::f32 sine   = std::sin(angle_);

	to_parent[0][0] = scale_[0] * cosine; to_parent[1][0] = scale_[1] *  -sine; to_parent[2][0] = position_[0];
	to_parent[0][1] = scale_[0] *   sine; to_parent[1][1] = scale_[1] * cosine; to_parent[2][1] = position_[1];
	to_parent[0][2] =               0.0f; to_parent[1][2] =               0.0f; to_parent[2][2] =         1.0f;
}



void Moveable2D::getFromParentTransformation(glm::mat3& from_parent) const
{
	JU::f32 cosine = std::cos(angle_);
	JU::f32 sine   = std::sin(angle_);
	JU::f32 inv_scalex  = 1.0f / scale_[0];
	JU::f32 inv_scaley  = 1.0f / scale_[1];

	from_parent[0][0] = cosine * inv_scalex;
	from_parent[1][0] =   sine * inv_scalex;
	from_parent[2][0] = -position_[0] * cosine * inv_scalex - position_[1] * sine * inv_scalex;

	from_parent[0][1] =  -sine * inv_scaley;
	from_parent[1][1] = cosine * inv_scaley;
	from_parent[2][1] =  position_[0] * sine * inv_scaley  - position_[1] * cosine * inv_scaley;

	from_parent[0][2] = 0.0f;
	from_parent[1][2] = 0.0f;
	from_parent[2][2] = 1.0f;
}


} /* namespace JU */
