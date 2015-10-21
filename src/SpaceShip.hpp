/*
 * SpaceShip.hpp
 *
 *  Created on: Oct 21, 2015
 *      Author: jusabiaga
 */

#ifndef SPACESHIP_HPP_
#define SPACESHIP_HPP_

#include "GameObject.hpp"		// GameObject
#include "Defs.hpp"				// JU::f32

namespace JU
{

class SpaceShip : public GameObject
{
	public:
		SpaceShip(f32 pos_x, f32 pos_y, f32 angle);
		virtual ~SpaceShip();

		void update(JU::f32 milliseconds) override;
		virtual void render(const GLSLProgram &program, const glm::mat3 & model, const glm::mat3 &view) const override;
};

} /* namespace JU */

#endif /* SPACESHIP_HPP_ */
