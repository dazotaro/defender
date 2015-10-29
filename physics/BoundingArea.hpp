/*
 * BoundingArea.hpp
 *
 *  Created on: Oct 29, 2015
 *      Author: jusabiaga
 */

#ifndef BOUNDINGAREA_HPP_
#define BOUNDINGAREA_HPP_

#include <glm/glm.hpp>			// vec2


namespace JU
{


class BoundingCircle
{
	public:
		BoundingCircle(const glm::vec2* vertices, int size);

		glm::vec2 center_;
		glm::f32  radius_;
};


class BoundingRectangle
{
	public:
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
