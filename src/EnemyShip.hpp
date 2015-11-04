/*
 * EnemyShip.hpp
 *
 *  Created on: Oct 21, 2015
 *      Author: jusabiaga
 */

#ifndef ENEMYSHIP_HPP_
#define ENEMYSHIP_HPP_

#include "../core/GameObject.hpp"		// GameObject
#include "../core/Defs.hpp"				// JU::f32

namespace JU
{

/*! EnemyShip class defining a generic enemy spaceship */
class EnemyShip: public GameObject
{
    public:
        EnemyShip(f32 posx, f32 posy, f32 angle,
                  f32 distance = 0.005f, f32 angle_delta = 0.003f,
                  const glm::vec4& color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

        virtual ~EnemyShip();

        void update(JU::f32 milliseconds) override;
        virtual void render(const GLSLProgram &program, const glm::mat3 & model,
                const glm::mat3 &view) const override;

    private:
        JU::f32 distance_;
        JU::f32 angle_delta_;
};

} /* namespace JU */

#endif /* ENEMYSHIP_HPP_ */
