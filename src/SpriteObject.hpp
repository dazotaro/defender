/*
 * SpriteObject.hpp
 *
 *  Created on: Nov 12, 2015
 *      Author: jusabiaga
 */

#ifndef SPRITEOBJECT_HPP_
#define SPRITEOBJECT_HPP_

// Local includes
#include "../core/GameObject.hpp"   // GameObject

namespace JU
{

class SpriteObject : public GameObject
{
    public:
        SpriteObject(const char* name, const char* texture_filename, bool is_collideable = false);
        virtual ~SpriteObject();

    public:
        void update(JU::f32 milliseconds) override;
        void render(const GLSLProgram &program, const glm::mat3 & model, const glm::mat3 &view) const override;
};

} /* namespace JU */

#endif /* SPRITEOBJECT_HPP_ */
