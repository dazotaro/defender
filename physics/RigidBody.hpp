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
class ShareableResource;

class RigidBody
{
    public:
        RigidBody(ShareableResource<BoundingCircle>* pboundingarea_resource, Moveable2D* pmoveable = nullptr);
        virtual ~RigidBody();

        void setMoveable(Moveable2D* pmoveable);
        const Moveable2D* getMoveable() const;
        const BoundingCircle* getBoundingArea() const;

    private:
        ShareableResource<BoundingCircle>* pboundingarea_resource_; //!< BoundingArea object for collision detection/resolution
        Moveable2D*                        pmoveable_;
};

} /* namespace JU */

#endif /* RIGIDBODY_HPP_ */
