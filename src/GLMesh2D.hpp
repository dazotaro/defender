/*
 * GLMesh2D.hpp
 *
 *  Created on: Oct 18, 2015
 *      Author: jusabiaga
 */

#ifndef GLMESH2D_HPP_
#define GLMESH2D_HPP_

#include "Defs.hpp"					// uint8
#include "gl_core_4_2.hpp"          // glLoadGen generated header file

class GLMesh2D
{
	public:
		GLMesh2D();
		virtual ~GLMesh2D();

		void init();

	private:
        GLuint vao_handle_;         //!< Handle to VAO
        GLuint *vbo_handles_;		//!< Handle to dynamically allocated VBOs
        JU::uint8 num_buffers_;
};

#endif /* GLMESH2D_HPP_ */
