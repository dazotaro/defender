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
// Global includes

namespace JU
{


template <typename T>
class RigidBody
{
	public:
		RigidBody();
		virtual ~RigidBody();

	private:
		BoundingArea<T> ba_;

};

} /* namespace JU */

#endif /* RIGIDBODY_HPP_ */
