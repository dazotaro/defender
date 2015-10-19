/*
 * Camera2D.hpp
 *
 *  Created on: Oct 19, 2015
 *      Author: jusabiaga
 */

#ifndef CAMERA2D_HPP_
#define CAMERA2D_HPP_

#include "Moveable2D.hpp"	// Moveable2D
#include "Defs.hpp"			// JU::uint32

namespace JU
{

class Camera2D
{
	public:
		Camera2D();
		Camera2D(Moveable2D moveable, JU::uint32 width, JU::uint32 height);

		void setMoveable(Moveable2D moveable);

	private:
		Moveable2D moveable_;	//!< Moveable data
		JU::uint32 width_;		//!< Width of the camera's window
		JU::uint32 height_;		//!< Height of the camera's window
};

} /* namespace JU */

#endif /* CAMERA2D_HPP_ */
