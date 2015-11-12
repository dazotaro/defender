/*
 * DynamicGridObject.hpp
 *
 *  Created on: Nov 12, 2015
 *      Author: jusabiaga
 */

#ifndef DYNAMICGRIDOBJECT_HPP_
#define DYNAMICGRIDOBJECT_HPP_

// Local includes
#include "../core/GameObject.hpp"   // GameObject

namespace JU
{

class DynamicGridObject : public GameObject
{
    public:
        explicit DynamicGridObject(const char* name, uint32 sizex, uint32 sizey);
        virtual ~DynamicGridObject();

    public:
        void update(JU::f32 milliseconds) override;
        void render(const GLSLProgram &program, const glm::mat3 & model, const glm::mat3 &view) const override;
};

} /* namespace JU */

#endif /* DYNAMICGRIDOBJECT_HPP_ */
