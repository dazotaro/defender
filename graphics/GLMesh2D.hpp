/*
 * GLMesh2D.hpp
 *
 *  Created on: Oct 18, 2015
 *      Author: jusabiaga
 */

#ifndef GLMESH2D_HPP_
#define GLMESH2D_HPP_

#include "../core/Defs.hpp"                     // uint8
#include "../graphics/gl_core_4_2.hpp"          // glLoadGen generated header file

namespace JU
{

// Forward declarations
class Mesh2D;

/**
 * Implements the OpenGL code around Mesh2D
 */
class GLMesh2D
{
    public:
        GLMesh2D();
        virtual ~GLMesh2D();

        void transferDataGPU(const Mesh2D& mesh, GLenum usage = gl::STATIC_DRAW);
        void releaseDataGPU();

        void render() const;

    private:
        GLuint      vao_handle_;	//!< Handle to VAO
        GLuint*     vbo_handles_;   //!< Handle to dynamically allocated VBOs
        JU::uint8   num_vbos_;		//!< Number of VBOs
        JU::uint32  num_indices_;   //!< Number of vertices
        GLenum      draw_mode_;		//!< OpenGL draw mode (GL_TRIANGLE, GL_TRIANGLE_FAN...)
};

} // namespace JU

#endif /* GLMESH2D_HPP_ */
