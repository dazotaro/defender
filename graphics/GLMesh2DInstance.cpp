/*
 * GLMesh2DInstance.cpp
 *
 *  Created on: Oct 19, 2015
 *      Author: jusabiaga
 */

#include "GLMesh2DInstance.hpp"
#include "GLMesh2D.hpp"                 // GLMesh2D
#include "GLSLProgram.hpp"              // GLSLProgram
#include "../core/Singleton.hpp"        // Singleton
#include "../core/ResourceManager.hpp"  // ResourceManager, ShareableResource

namespace JU
{

GLMesh2DInstance::GLMesh2DInstance(ShareableResource<GLMesh2D>* pmesh_resource, const glm::vec4& color)
                    : pmesh_resource_(pmesh_resource), color_(color)
{
}


GLMesh2DInstance::~GLMesh2DInstance()
{
    Singleton<ResourceManager<GLMesh2D>>::getInstance()->releaseResource(pmesh_resource_);
}


const GLMesh2D* GLMesh2DInstance::getGLMesh() const
{
    return pmesh_resource_->pdata_;
}


void GLMesh2DInstance::render(const GLSLProgram &program, const glm::mat3 & model, const glm::mat3 &view) const
{
    glm::mat3 MV = view * model;

    // LOAD UNIFORMS
    program.setUniform("M", model);
    program.setUniform("MV", MV);
    program.setUniform("color", color_);

    // Tell the GLMesh2D to render
    pmesh_resource_->pdata_->render();
}

} /* namespace JU */
