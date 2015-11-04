/*
 * BoundingArea.cpp
 *
 *  Created on: Oct 29, 2015
 *      Author: jusabiaga
 */

#include "BoundingArea.hpp"
#include "Geometry.hpp"		// computeBoundingRectable

#include <cstdio>			// std::printf
#include <cstdlib>			// std::exit

namespace JU
{

BoundingCircle::BoundingCircle(const glm::vec2 center, f32 radius) :
        center_(center), radius_(radius)
{
}

BoundingCircle::BoundingCircle(const glm::vec2* vertices, int size)
{
    glm::vec2 pmin, pmax;

    if (!computeBoundingRectangle(vertices, size, pmin, pmax))
    {
        std::printf("Error computing bounding rectangle\n");
        exit(EXIT_FAILURE);
    }

    center_ = (pmin + pmax) * 0.5f;
    radius_ = glm::distance(pmin, pmax) * 0.5f;
}

BoundingRectangle::BoundingRectangle(const glm::vec2 pmin, const glm::vec2 pmax) :
        pmin_(pmin), pmax_(pmax)
{

}

BoundingRectangle::BoundingRectangle(const glm::vec2* vertices, int size)
{
    if (!computeBoundingRectangle(vertices, size, pmin_, pmax_))
    {
        std::printf("Error computing bounding rectangle\n");
        exit(EXIT_FAILURE);
    }
}

template<typename T>
BoundingArea<T>::BoundingArea()
{
    // TODO Auto-generated constructor stub

}

template<typename T>
BoundingArea<T>::~BoundingArea()
{
    // TODO Auto-generated destructor stub
}

} /* namespace JU */
