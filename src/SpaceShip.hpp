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
		SpaceShip(f32 posx, f32 posy, f32 angle, f32 distance = 0.003f, f32 angle_delta = 0.003f);
		virtual ~SpaceShip();

		void update(JU::f32 milliseconds) override;
		virtual void render(const GLSLProgram &program, const glm::mat3 & model, const glm::mat3 &view) const override;

	private:
		JU::f32 distance_;
		JU::f32 angle_delta_;
};

} /* namespace JU */

#endif /* SPACESHIP_HPP_ */
