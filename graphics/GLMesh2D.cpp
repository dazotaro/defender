/*
 * GLMesh2D.cpp
 *
 *  Created on: Oct 18, 2015
 *      Author: jusabiaga
 */

// Local includes
#include "GLMesh2D.hpp"
#include "Mesh2D.hpp"       // Mesh2D
// Global includes
#include <cstdio>           // std::printf


namespace JU
{
/**
* @brief Default constructor
*
*/
GLMesh2D::GLMesh2D() : vao_handle_(0), vbo_handles_(nullptr), num_buffers_(0), num_indices_(0), draw_mode_(gl::TRIANGLES)
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
void GLMesh2D::init(const Mesh2D& pmesh)
{
    /*
    const float vertexPositions[] = {
        -0.75f, 0.75f, 0.0f, 1.0f,  // V0
        -0.75f, -0.75f, 0.0f, 1.0f, // V1
        0.75f, 0.75f, 0.0f, 1.0f,   // V2
        0.75f, -0.75f, 0.0f, 1.0f,  // V3
    };
    */

    // Retrieve mesh data from Mesh2D object
    const glm::vec2*    pvertices = nullptr;
    JU::uint32          num_vertices = 0;
    const JU::uint32*   pindices = nullptr;
    JU::uint32          num_indices = 0;

    pmesh.getData(&pvertices, num_vertices, &pindices, num_indices, draw_mode_);

    // Transfer all vertex positions from 2D to Homogeneous coordinates
    f32* vertexPositions = new f32[num_vertices * 3];
    for (uint32 i = 0; i < num_vertices; ++i)
    {
        vertexPositions[i*3 + 0] = pvertices[i][0];
        vertexPositions[i*3 + 1] = pvertices[i][1];
        vertexPositions[i*3 + 2] = 1.0f;
    }

    JU::uint32* vertexIndices = new uint32[num_indices];
    for (uint32 i = 0; i < num_indices; ++i)
    {
        vertexIndices[i] = pindices[i];
    }

    num_indices_ = num_indices;

    // VAO
    gl::GenVertexArrays(1, &vao_handle_);
    gl::BindVertexArray(vao_handle_);

    // VBO
    vbo_handles_ = new GLuint[2];
    gl::GenBuffers(2, vbo_handles_);

    // Allocate and initialize VBO for vertex positions
    gl::BindBuffer(gl::ARRAY_BUFFER, vbo_handles_[0]);
    gl::BufferData(gl::ARRAY_BUFFER, sizeof(vertexPositions[0]) * num_vertices * 3, vertexPositions, gl::STATIC_DRAW);
    // Insert the VBO into the VAO
    gl::EnableVertexAttribArray(0);
    gl::VertexAttribPointer(0, 3, gl::FLOAT, gl::FALSE_, 0, 0);

    // Allocate and initialize VBO for vertex indices
    gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, vbo_handles_[1]);
    gl::BufferData(gl::ELEMENT_ARRAY_BUFFER, sizeof(vertexIndices[0]) * num_indices_, vertexIndices, gl::STATIC_DRAW);

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
    gl::DrawElements(draw_mode_, num_indices_, gl::UNSIGNED_INT, 0);

    // Unbind
    gl::BindVertexArray(0);
}


} // namespace JU

