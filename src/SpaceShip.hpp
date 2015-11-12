/*
 * SpaceShip.hpp
 *
 *  Created on: Oct 21, 2015
 *      Author: jusabiaga
 */

#ifndef SPACESHIP_HPP_
#define SPACESHIP_HPP_

#include "SpriteObject.hpp"		// SpriteObject
#include "../core/Defs.hpp"	    // JU::f32

namespace JU
{

/*! SpaceShip class defining a 'protagonist' SpaceShip */
class SpaceShip: public SpriteObject
{
    public:
        SpaceShip(const char* name, const char* texture_filename, bool is_collideable = false, f32 distance = 0.005f, f32 angle_delta = 0.003f);
        virtual ~SpaceShip();

        void update(JU::f32 milliseconds) override;

    private:
        JU::f32 distance_;
        JU::f32 angle_delta_;
};

} /* namespace JU */

#endif /* SPACESHIP_HPP_ */
