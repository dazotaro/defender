/*
 * Camera2D.hpp
 *
 *  Created on: Oct 19, 2015
 *      Author: jusabiaga
 */

#ifndef CAMERA2D_HPP_
#define CAMERA2D_HPP_

#include "../core/Moveable2D.hpp"   // Moveable2D
#include "../core/Defs.hpp"         // JU::uint32

namespace JU
{

class Camera2D
{
    public:
        Camera2D();
        Camera2D(Moveable2D moveable);

        // Getters
        const Moveable2D& getMoveable() const;
        Moveable2D& getMoveable();

        // Setters
        void setMoveable(Moveable2D moveable);
        void getWorld2NDCTransformation(glm::mat3& view) const;

    private:
        Moveable2D moveable_;   //!< Moveable data
};

} /* namespace JU */

#endif /* CAMERA2D_HPP_ */
