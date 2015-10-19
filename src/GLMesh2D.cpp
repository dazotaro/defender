/*
 * GLMesh2D.cpp
 *
 *  Created on: Oct 18, 2015
 *      Author: jusabiaga
 */

#include "GLMesh2D.hpp"

namespace JU
{
/**
* @brief Default constructor
*
*/
GLMesh2D::GLMesh2D() : vao_handle_(0), vbo_handles_(nullptr), num_buffers_(0), num_vertices_(0)
{
}


/**
* @brief Destructor
*
*/
GLMesh2D::~GLMesh2D()
{
}


/**
* @brief Initialization function
*
* @detail Set up the VBOs and VAO
*/
void GLMesh2D::init()
{
    const float vertexPositions[] = {
        -0.75f, 0.75f, 0.0f, 1.0f,  // V0
        -0.75f, -0.75f, 0.0f, 1.0f, // V1
        0.75f, 0.75f, 0.0f, 1.0f,   // V2
        0.75f, -0.75f, 0.0f, 1.0f,  // V3
    };

    const unsigned short vertexIndices[] = {
        // First triangle: upper left
        0, 1, 2,
        // Second triangle: bottom right
        1, 3, 2,
    };

    num_vertices_ = sizeof(vertexIndices) / sizeof(vertexIndices[0]);

    // VAO
    gl::GenVertexArrays(1, &vao_handle_);
    gl::BindVertexArray(vao_handle_);

    // VBO
    vbo_handles_ = new GLuint[2];
    gl::GenBuffers(2, vbo_handles_);

    // Allocate and initialize VBO for vertex positions
    gl::BindBuffer(gl::ARRAY_BUFFER, vbo_handles_[0]);
    gl::BufferData(gl::ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, gl::STATIC_DRAW);
    // Insert the VBO into the VAO
    gl::EnableVertexAttribArray(0);
    gl::VertexAttribPointer(0, 4, gl::FLOAT, gl::FALSE_, 0, 0);

    // Allocate and initialize VBO for vertex indices
    gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, vbo_handles_[1]);
    gl::BufferData(gl::ELEMENT_ARRAY_BUFFER, sizeof(vertexIndices), vertexIndices, gl::STATIC_DRAW);

    // Unbind
    gl::BindBuffer(gl::ARRAY_BUFFER, 0);
    gl::BindVertexArray(0);
}


/**
* @brief Render function
*
* @detail Render this GLMesh2D
*
* @param program GLSLProgram to use for rendering
*
*/
void GLMesh2D::render() const
{
    gl::BindVertexArray(vao_handle_);

    // Draw using indices
    gl::DrawElements(gl::TRIANGLES, num_vertices_, gl::UNSIGNED_SHORT, 0);

    // Unbind
    gl::BindVertexArray(0);
}


} // namespace JU

