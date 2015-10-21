/*
 * Renderable2DInterface.hpp
 *
 *  Created on: Oct 19, 2015
 *      Author: jusabiaga
 */

#ifndef RENDERABLE2DINTERFACE_HPP_
#define RENDERABLE2DINTERFACE_HPP_

#include <glm/glm.hpp>      // glm::mat3
#include <vector>           // std::vector

namespace JU
{

// FORWARD DECLARATIONS
class GLSLProgram;
class Moveable2D;

/**
 * @brief      Pure Virtual Class to draw objects
 *
 * @details    All derived classes will need to implement the 'draw' function
 */
class Renderable2DInterface
{
    public:
        virtual ~Renderable2DInterface() {}
        virtual void render(const GLSLProgram &program, const glm::mat3 & model, const glm::mat3 &view) const = 0;
};

} // namespace JU


#endif /* RENDERABLE2DINTERFACE_HPP_ */
