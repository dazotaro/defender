/*
 * GLMesh2DInstance.cpp
 *
 *  Created on: Oct 19, 2015
 *      Author: jusabiaga
 */

#include "GLMesh2DInstance.hpp"
#include "GLMesh2D.hpp"             // GLMesh2D
#include "GLSLProgram.hpp"          // GLSLProgram

namespace JU
{

GLMesh2DInstance::GLMesh2DInstance(const GLMesh2D* gl_mesh, const glm::vec4& color) : gl_mesh_(gl_mesh), color_(color)
{
}


GLMesh2DInstance::~GLMesh2DInstance()
{
    // TODO Auto-generated destructor stub
}


void GLMesh2DInstance::render(const GLSLProgram &program, const glm::mat3 & model, const glm::mat3 &view) const
{
    glm::mat3 MV = view * model;

    // LOAD UNIFORMS
    program.setUniform("M", model);
    program.setUniform("MV", MV);
    program.setUniform("color", color_);

    // Tell the GLMesh2D to render
    gl_mesh_->render();
}

} /* namespace JU */
