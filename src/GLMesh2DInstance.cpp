/*
 * GLMesh2DInstance.cpp
 *
 *  Created on: Oct 19, 2015
 *      Author: jusabiaga
 */

#include "GLMesh2DInstance.hpp"
#include "GLMesh2D.hpp"				// GLMesh2D

namespace JU
{

GLMesh2DInstance::GLMesh2DInstance(const GLMesh2D* gl_mesh, const glm::vec2& scale) : gl_mesh_(gl_mesh), scale_(scale)
{
}


GLMesh2DInstance::~GLMesh2DInstance()
{
	// TODO Auto-generated destructor stub
}


void GLMesh2DInstance::render(const GLSLProgram &program, const glm::mat3 & model, const glm::mat3 &view) const
{
	glm::mat3 scale(scale_[0],      0.0f, 0.0f,
						 0.0f, scale_[1], 0.0f,
						 0.0f,      0.0f, 1.0f);
	glm::mat3 M  = model * scale;
	glm::mat3 MV = view * M;

	// Set Uniforms with our matrices

	// Tell the GLMesh2D to render
	gl_mesh_->render();
}

} /* namespace JU */
