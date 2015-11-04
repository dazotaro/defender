/*
 * GLMesh2DInstance.hpp
 *
 *  Created on: Oct 19, 2015
 *      Author: jusabiaga
 */

#ifndef GLMESH2DINSTANCE_HPP_
#define GLMESH2DINSTANCE_HPP_

#include "Renderable2DInterface.hpp"    // Renderable2DInterface

namespace JU
{

template <typename T>
class ShareableResource;

// Forward Declarations
class GLMesh2D;

class GLMesh2DInstance : public Renderable2DInterface
{
    public:
        GLMesh2DInstance(ShareableResource<GLMesh2D>* pmesh_resource = nullptr, const glm::vec4& color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        virtual ~GLMesh2DInstance();

    public:
        const GLMesh2D* getGLMesh() const;
        // Renderable2DInterface
        void render(const GLSLProgram &program, const glm::mat3 & model, const glm::mat3 &view) const;

    private:
        ShareableResource<GLMesh2D>* pmesh_resource_;
        glm::vec4                    color_;
};

} /* namespace JU */

#endif /* GLMESH2DINSTANCE_HPP_ */
