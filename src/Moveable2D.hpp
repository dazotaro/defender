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
				   glm::f32 scalex = 1.0f, glm::f32 scaley = 1.0f,
				   glm::f32 angle = 0.0f);

		glm::mat3 transformationToParent() const;
		glm::mat3 transformationFromParent() const;

	private:
		glm::vec2	position_;	//!< position in parent's coordinate system
		glm::vec2	scale_;		//!< scale
		glm::f32	angle_;		//!< angle with the parent's X axis (in radians)
};

} /* namespace JU */

#endif /* MOVEABLE2D_HPP_ */
