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


void GLMesh2DInstance::render(const GLSLProgram &program,	const glm::mat3 & model, const glm::mat3 &view) const
{
	gl_mesh_->render();
}

} /* namespace JU */
