/*
 * GLMesh2D.hpp
 *
 *  Created on: Oct 18, 2015
 *      Author: jusabiaga
 */

#ifndef GLMESH2D_HPP_
#define GLMESH2D_HPP_

#include "Defs.hpp"						// uint8
#include "gl_core_4_2.hpp"          	// glLoadGen generated header file
#include "Renderable2DInterface.hpp"	// Renderable2DInterface

namespace JU
{

class GLMesh2D : public Renderable2DInterface
{
	public:
		GLMesh2D();
		virtual ~GLMesh2D();

		void init();
		void render() const;

		// Renderable2DInterface
        virtual void render(const GLSLProgram &program,
                          const glm::mat3 & model,
                          const glm::mat3 &view) const;


	private:
        GLuint vao_handle_;         //!< Handle to VAO
        GLuint *vbo_handles_;		//!< Handle to dynamically allocated VBOs
        JU::uint8 num_buffers_;
        JU::uint32 num_vertices_;	//!< Number of vertices
};

} // namespace JU

#endif /* GLMESH2D_HPP_ */
