/*
 * GLMesh2DInstance.hpp
 *
 *  Created on: Oct 19, 2015
 *      Author: jusabiaga
 */

#ifndef GLMESH2DINSTANCE_HPP_
#define GLMESH2DINSTANCE_HPP_

#include "Renderable2DInterface.hpp"    // Renderable2DInterface
#include "Texture.hpp"                  // Texture

namespace JU
{

// Forward Declarations
class GLMesh2D;
template <typename T>
class Shareable;

/**
 * OpenGL code for a 2D Mesh instance (geometry, texture, color)
 */
class GLMesh2DInstance : public Renderable2DInterface
{
    public:
        GLMesh2DInstance(Shareable<const GLMesh2D>* pshare_mesh = nullptr,
                         Shareable<const Texture>* pshare_texture = nullptr,
                         const glm::vec4& color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        virtual ~GLMesh2DInstance();

    public:
        // Getters
        const GLMesh2D* getGLMesh() const;

        // Setters
        void setColor(const glm::vec4& color);

        // Renderable2DInterface
        void render(const GLSLProgram &program, const glm::mat3 & model, const glm::mat3 &view) const;

    private:
        Shareable<const GLMesh2D>*  pshare_mesh_;		//!< Shareable mesh
        Shareable<const Texture>*   pshare_texture_;	//!< Shareable texture
        glm::vec4                   color_;				//!< Color
};

} /* namespace JU */

#endif /* GLMESH2DINSTANCE_HPP_ */
