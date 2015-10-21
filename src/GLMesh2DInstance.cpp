/*
 * GLMesh2DInstance.cpp
 *
 *  Created on: Oct 19, 2015
 *      Author: jusabiaga
 */

#include "GLMesh2DInstance.hpp"
#include "GLMesh2D.hpp"				// GLMesh2D
#include "GLSLProgram.hpp"			// GLSLProgram
#include <cstdio>					// printf

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

	std::printf("M = \n");
	std::printf("%g %g %g\n%g %g %g\n%g %g %g\n", M[0][0], M[0][1], M[0][2], M[1][0], M[1][1], M[1][2], M[2][0], M[2][1], M[2][2]);
	std::printf("V = \n");
	std::printf("%g %g %g\n%g %g %g\n%g %g %g\n", view[0][0], view[0][1], view[0][2], view[1][0], view[1][1], view[1][2], view[2][0], view[2][1], view[2][2]);
	std::printf("MV = \n");
	std::printf("%g %g %g\n%g %g %g\n%g %g %g\n", MV[0][0], MV[0][1], MV[0][2], MV[1][0], MV[1][1], MV[1][2], MV[2][0], MV[2][1], MV[2][2]);

    // LOAD UNIFORMS
    program.setUniform("M", M);
    program.setUniform("MV", MV);

	// Tell the GLMesh2D to render
	gl_mesh_->render();
}

} /* namespace JU */
