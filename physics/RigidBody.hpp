/*
 * RigidBody.hpp
 *
 *  Created on: Oct 29, 2015
 *      Author: jusabiaga
 */

#ifndef RIGIDBODY_HPP_
#define RIGIDBODY_HPP_

// Local includes
#include "BoundingArea.hpp"

namespace JU
{

// Forward declarations
class Moveable2D;

template <typename T>
class Shareable;

class RigidBody
{
    public:
        RigidBody(Shareable<BoundingCircle>* pshare_boundingbox, Moveable2D* pmoveable = nullptr);
        virtual ~RigidBody();

        void setMoveable(Moveable2D* pmoveable);
        const Moveable2D* getMoveable() const;
        const BoundingCircle* getBoundingArea() const;

    private:
        Shareable<BoundingCircle>* pshare_boundingbox_; //!< BoundingArea object for collision detection/resolution
        Moveable2D*                pmoveable_;
};

} /* namespace JU */

#endif /* RIGIDBODY_HPP_ */
