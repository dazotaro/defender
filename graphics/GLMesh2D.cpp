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
GLMesh2D::GLMesh2D() : vao_handle_(0), vbo_handles_(nullptr), num_vbos_(0), num_indices_(0), draw_mode_(gl::TRIANGLES)
{
}


/**
* @brief Destructor
*
*/
GLMesh2D::~GLMesh2D()
{
    releaseDataGPU();
}


/**
* @brief Release the data stored in the GPU
*
* @detail Release the VBOs and VAOs storing the mesh data in the GPU
*
*/
void GLMesh2D::releaseDataGPU()
{
    gl::DeleteBuffers(num_vbos_, vbo_handles_);
    delete [] vbo_handles_;
    gl::DeleteVertexArrays(1, &vao_handle_);
}


/**
* @brief Transfer the mesh data to the GPU
*
* @detail Transfer the mesh data to the GPU
*
* @param mesh  Mesh2D object with the mesh
* @param usage Hint for glBufferData: GL_STATIC_DRAW, GL_DYNAMIC_DRAW
*
*/
void GLMesh2D::transferDataGPU(const Mesh2D& mesh, GLenum usage)
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
    const glm::vec2*    ptexcoordinates = nullptr;

    mesh.getData(&pvertices, num_vertices, &pindices, num_indices, draw_mode_, &ptexcoordinates);

    // VERTICES
    // Transfer all vertex positions from 2D to Homogeneous coordinates
    f32* vertexPositions = new f32[num_vertices * 3];
    for (uint32 i = 0; i < num_vertices; ++i)
    {
        vertexPositions[i*3 + 0] = pvertices[i][0];
        vertexPositions[i*3 + 1] = pvertices[i][1];
        vertexPositions[i*3 + 2] = 1.0f;
    }

    // INDICES
    JU::uint32* vertexIndices = new uint32[num_indices];
    for (uint32 i = 0; i < num_indices; ++i)
    {
        vertexIndices[i] = pindices[i];
    }

    num_indices_ = num_indices;

    num_vbos_ = 2;
    if (ptexcoordinates)
        num_vbos_ = 3;

    // VAO
    gl::GenVertexArrays(1, &vao_handle_);
    gl::BindVertexArray(vao_handle_);

    // VBO
    vbo_handles_ = new GLuint[num_vbos_];
    gl::GenBuffers(num_vbos_, vbo_handles_);

    // Allocate and initialize VBO for vertex positions
    gl::BindBuffer(gl::ARRAY_BUFFER, vbo_handles_[0]);
    gl::BufferData(gl::ARRAY_BUFFER, sizeof(vertexPositions[0]) * num_vertices * 3, vertexPositions, usage);
    // Insert the VBO into the VAO
    gl::EnableVertexAttribArray(0);
    gl::VertexAttribPointer(0, 3, gl::FLOAT, gl::FALSE_, 0, 0);

    // Allocate and initialize VBO for vertex indices
    gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, vbo_handles_[1]);
    gl::BufferData(gl::ELEMENT_ARRAY_BUFFER, sizeof(vertexIndices[0]) * num_indices_, vertexIndices, gl::STATIC_DRAW);

    if (ptexcoordinates)
    {
        gl::BindBuffer(gl::ARRAY_BUFFER, vbo_handles_[2]);
        gl::BufferData(gl::ARRAY_BUFFER, sizeof(ptexcoordinates[0]) * num_vertices, ptexcoordinates, gl::STATIC_DRAW);
        // Insert the VBO into the VAO
        gl::EnableVertexAttribArray(1);
        gl::VertexAttribPointer(1, 2, gl::FLOAT, gl::FALSE_, 0, 0);
    }
    // Unbind
    gl::BindBuffer(gl::ARRAY_BUFFER, 0);
    gl::BindVertexArray(0);

    delete [] vertexPositions;
    delete [] vertexIndices;
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

