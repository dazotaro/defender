/*
 * Geometry.cpp
 *
 *  Created on: Oct 29, 2015
 *      Author: jusabiaga
 */

// Local includes
#include "Geometry.hpp"
// Global includes
#include <cstdio>		// std::printf

namespace JU
{

bool computeBoundingRectangle(const glm::vec2* points, int size,
        glm::vec2& pmin, glm::vec2& pmax)
{
    if (size == 0)
    {
        return false;
    }
    else
    {
        pmin = points[0];
        pmax = points[0];

        for (int index = 0; index < size; ++index)
        {
            // X axis
            if (points[index][0] < pmin[0])
            {
                pmin[0] = points[index][0];
            }
            else if (points[index][0] > pmax[0])
            {
                pmax[0] = points[index][0];
            }
            // Y axis
            if (points[index][1] < pmin[1])
            {
                pmin[1] = points[index][1];
            }
            else if (points[index][1] > pmax[1])
            {
                pmax[1] = points[index][1];
            }
        }
    }

    return true;
}

bool testCollision(const BoundingCircle& circle1, const BoundingCircle& circle2)
{
    /*
     std::printf("(%f, %f --- %f) and (%f, %f --- %f)\n",
     circle1.center_[0],
     circle1.center_[1],
     circle1.radius_,
     circle2.center_[0],
     circle2.center_[1],
     circle2.radius_);
     std::printf("distance = %f, radiuses = %f\n",
     glm::distance(circle1.center_, circle2.center_),
     (circle1.radius_ + circle2.radius_));
     */
    if (glm::distance(circle1.center_, circle2.center_)
            < (circle1.radius_ + circle2.radius_))
    {
        return true;
    }

    return false;
}

bool testCollision(const BoundingRectangle& rec1, const BoundingRectangle& rec2)
{
    if ((((rec1.pmax_[0] > rec2.pmin_[0]) && (rec1.pmax_[0] < rec2.pmax_[0]))
            || ((rec1.pmin_[0] < rec2.pmax_[0])
                    && (rec1.pmin_[0] > rec2.pmin_[0])))
            && (((rec1.pmax_[1] > rec2.pmin_[1])
                    && (rec1.pmax_[1] < rec2.pmax_[1]))
                    || ((rec1.pmin_[1] < rec2.pmax_[1])
                            && (rec1.pmin_[1] > rec2.pmin_[1]))))
        return true;

    return false;
}

} // namespace JU
