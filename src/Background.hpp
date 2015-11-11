/*
 * Background.hpp
 *
 *  Created on: Oct 21, 2015
 *      Author: jusabiaga
 */

#ifndef BACKGROUND_HPP_
#define BACKGROUND_HPP_

#include "../core/GameObject.hpp"		// GameObject
#include "../core/Defs.hpp"				// JU::f32

namespace JU
{

/*! Background class defining a generic enemy spaceship */
class Background: public GameObject
{
    public:
        Background(f32 posx, f32 posy, f32 angle);

        virtual ~Background();

        void update(JU::f32 milliseconds) override;
        void render(const GLSLProgram &program, const glm::mat3 & model, const glm::mat3 &view) const override;
};

} /* namespace JU */

#endif /* BACKGROUND_HPP_ */
