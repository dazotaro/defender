/*
 * BoundingArea.hpp
 *
 *  Created on: Oct 29, 2015
 *      Author: jusabiaga
 */

#ifndef BOUNDINGAREA_HPP_
#define BOUNDINGAREA_HPP_

#include "../core/Defs.hpp"		// f32
#include <glm/glm.hpp>			// vec2


namespace JU
{


class BoundingCircle
{
	public:
		BoundingCircle() : center_(glm::vec2(0.0f, 0.0f)), radius_(0.0f) {};
		BoundingCircle(const glm::vec2 center, f32 radius);
		BoundingCircle(const glm::vec2* vertices, int size);

		glm::vec2 center_;
		f32  	  radius_;
};


class BoundingRectangle
{
	public:
		BoundingRectangle(const glm::vec2 pmin, const glm::vec2 pmax);
		BoundingRectangle(const glm::vec2* vertices, int size);

		glm::vec2 pmin_;
		glm::vec2 pmax_;
};


template <typename T>
class BoundingArea
{
	public:
		BoundingArea();
		virtual ~BoundingArea();

	private:
		T area_;
};

} /* namespace JU */

#endif /* BOUNDINGAREA_HPP_ */
