/*
 * Moveable2D.hpp
 *
 *  Created on: Oct 19, 2015
 *      Author: jusabiaga
 */

#ifndef MOVEABLE2D_HPP_
#define MOVEABLE2D_HPP_

#include <glm/glm.hpp>		// glm::vec3

namespace JU
{

class Moveable2D
{
	public:
		Moveable2D(glm::f32 pos_x = 0.0f, glm::f32 pos_y = 0.0f,
				   glm::f32 angle = 0.0f);

		void getToParentTransformation  (glm::mat3& to_parent) const;
		void getFromParentTransformation(glm::mat3& from_parent) const;

	public:
		glm::vec2	position_;	//!< position in parent's coordinate system
		glm::f32	angle_;		//!< angle with the parent's X axis (in radians)
};

} /* namespace JU */

#endif /* MOVEABLE2D_HPP_ */
