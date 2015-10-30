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

class RigidBody
{
	public:
		RigidBody(const BoundingCircle& bounding_area, Moveable2D* pmoveable = nullptr);
		virtual ~RigidBody();

		void setMoveable(Moveable2D* pmoveable) { pmoveable_ = pmoveable; }
		const Moveable2D* getMoveable() const { return pmoveable_; }
		const BoundingCircle& getBoundingArea() const { return bounding_area_; }

	private:
		BoundingCircle bounding_area_;  //!< BoundingArea object for collision detection/resolution
		Moveable2D*	   pmoveable_;
};


} /* namespace JU */

#endif /* RIGIDBODY_HPP_ */
