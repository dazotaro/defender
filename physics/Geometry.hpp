#ifndef GEOMETRY_HPP_
#define GEOMETRY_HPP_

#include "BoundingArea.hpp"     // BoundingArea, BoundingCircle, BoundingRectangle

namespace JU
{

// Bounding Areas
// --------------
bool computeBoundingRectangle(const glm::vec2* points, int size,
        glm::vec2& pmin, glm::vec2& pmax);

// Collision Tests
// --------------
bool testCollision(const BoundingCircle& circle1,
        const BoundingCircle& circle2);
bool testCollision(const BoundingRectangle& rec1,
        const BoundingRectangle& rec2);

} // namespace JU

#endif // GEOMETRY_HPP_

