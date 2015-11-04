/*
 * Moveable2D.hpp
 *
 *  Created on: Oct 19, 2015
 *      Author: jusabiaga
 */

#ifndef MOVEABLE2D_HPP_
#define MOVEABLE2D_HPP_

#include <glm/glm.hpp>      // glm::vec3
#include "Defs.hpp"         // f32

namespace JU
{

class Moveable2D
{
    public:
        Moveable2D(JU::f32 posx = 0.0f, JU::f32 posy = 0.0f, JU::f32 angle = 0.0f,
                   JU::f32 scalex = 1.0f, JU::f32 scaley = 1.0f);

        void getToParentTransformation  (glm::mat3& to_parent) const;
        void getFromParentTransformation(glm::mat3& from_parent) const;

        void moveX(JU::f32 distance);
        void moveY(JU::f32 distance);
        void rotate(JU::f32 angle);

    public:
        glm::vec2   position_;  //!< position in parent's coordinate system
        JU::f32 angle_;     //!< angle with the parent's X axis (in radians)
        glm::vec2   scale_;     //!< scale
};

} /* namespace JU */

#endif /* MOVEABLE2D_HPP_ */
