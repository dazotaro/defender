/*
 * DynamicGrid.cpp
 *
 *  Created on: Nov 12, 2015
 *      Author: jusabiaga
 */

#include "DynamicGrid.hpp"
#include "../graphics/GLSLProgram.hpp"      // GLSLProgram
#include "../core/Keyboard.hpp"             // Keyboard
#include "../core/Singleton.hpp"            // Singleton
#include "../core/Moveable2D.hpp"           // Moveable2D
#include "../core/Singleton.hpp"            // Singleton
#include "../core/ResourceManager.hpp"      // ResourceManager
#include "../physics/RigidBody.hpp"         // RigidBody

namespace JU
{

/**
 * @brief Non-default constructor
 *
 * @param posx  X coordinate of position
 * @param posy  Y coordinate of position
 * @param angle Angle of orientation in radians
 *
 */
template <uint32 SIZEX, uint32 SIZEY>
DynamicGrid<SIZEX, SIZEY>::DynamicGrid(Moveable2D moveable, f32 mass, const glm::vec4& color)
                : moveable_(moveable), mass_(mass), vao_(0), color_(color)
{
    const f32 width  = 1.0f;
    const f32 height = 1.0f;
    const f32 xinc =  width / (SIZEX - 1);
    const f32 yinc = height / (SIZEY - 1);

    // POSITIONS
    f32 x = -width / 2.0f;
    for (uint32 i = 0; i < SIZEX; ++i)
    {
        f32 y = -height / 2.0;
        for (uint32 j = 0; j < SIZEY; ++j)
        {
            pvertices_[i*SIZEY + j][0] = x;
            pvertices_[i*SIZEY + j][1] = y;
            pvertices_[i*SIZEY + j][2] = 1.0f;

            y += yinc;
        }
        x += xinc;
    }

    // INDICES
    uint32 index = 0;
    for (uint32 i = 0; i < SIZEX; ++i)
    {
        for (uint32 j = 0; j < SIZEY; ++j)
        {
            if (i > 0)
            {
                // Line to the WEST vertex
                pindices_[index++] = (i-1) * SIZEY + j;
                pindices_[index++] =     i * SIZEY + j;
            }
            if (j > 0)
            {
                // Line to the NORTH vertex
                pindices_[index++] = i * SIZEY + (j-1);
                pindices_[index++] = i * SIZEY + j;
            }
        }
    }


    // Transfer the data to the GPU
    // -------------
    // VAO
    gl::GenVertexArrays(1, &vao_);
    gl::BindVertexArray(vao_);

    // VBO
    gl::GenBuffers(NUM_VBOS, pvbos_);

    // Allocate and initialize VBO for vertex positions
    gl::BindBuffer(gl::ARRAY_BUFFER, pvbos_[0]);
    gl::BufferData(gl::ARRAY_BUFFER, sizeof(pvertices_), pvertices_, gl::DYNAMIC_DRAW);
    // Insert the VBO into the VAO
    gl::EnableVertexAttribArray(0);
    gl::VertexAttribPointer(0, 3, gl::FLOAT, gl::FALSE_, 0, 0);

    // Allocate and initialize VBO for vertex indices
    gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, pvbos_[1]);
    gl::BufferData(gl::ELEMENT_ARRAY_BUFFER, sizeof(pindices_), pindices_, gl::STATIC_DRAW);

    // Unbind
    gl::BindBuffer(gl::ARRAY_BUFFER, 0);
    gl::BindVertexArray(0);
}

/**
 * @brief Destructor
 *
 */
template <uint32 SIZEX, uint32 SIZEY>
DynamicGrid<SIZEX, SIZEY>::~DynamicGrid()
{
    gl::DeleteBuffers(NUM_VBOS, pvbos_);
    gl::DeleteVertexArrays(1, &vao_);
}


/**
 * @brief Get Moveable2D (const version)
 *
 * @return Moveable2D object
 *
 */
template <uint32 SIZEX, uint32 SIZEY>
const Moveable2D& DynamicGrid<SIZEX, SIZEY>::getMoveable() const
{
    return moveable_;
}


/**
 * @brief Get Moveable2D
 *
 * @return Moveable2D object
 *
 */
template <uint32 SIZEX, uint32 SIZEY>
Moveable2D& DynamicGrid<SIZEX, SIZEY>::getMoveable()
{
    return moveable_;
}


/**
 * @brief Set Position of the focus of waves
 *
 * @param x  X coordinate of focus
 * @param y  Y coordinate of focus
 *
 */
template <uint32 SIZEX, uint32 SIZEY>
void DynamicGrid<SIZEX, SIZEY>::setPosition(f32 x, f32 y)
{
    moveable_.position_[0] = x;
    moveable_.position_[1] = x;
}


/**
 * @brief Update function
 *
 * @param milliseconds  Time elapsed since the last call (in milliseconds)
 *
 */
template <uint32 SIZEX, uint32 SIZEY>
void DynamicGrid<SIZEX, SIZEY>::update(f32 milliseconds, const glm::vec2* force_locations, uint32 num_forces)
{
    // Update time since beginning of execution
    static f32 elapsed_time = milliseconds;
    elapsed_time += milliseconds;

    static const uint32 num_vertices = SIZEX * SIZEY;

    glm::vec3* pnew_vertices = new glm::vec3[num_vertices]();

    glm::mat3 model;
    moveable_.getToParentTransformation(model);

    if (num_vertices)
    {
        //glm::vec2 origin(0.0f, 0.0f);
        glm::vec2 origin(moveable_.position_);
        f32 amplitud = 0.01f * moveable_.scale_[0];
        const f32 freq = 8.0f;
        f32 angle = 2.0f * M_PI * freq / moveable_.scale_[0];
        //f32 phase = elapsed_time * 2.0f * M_PI * 0.001f;
        f32 phase = 0.0f;

        for (uint32 i = 0; i < num_vertices; ++i)
        {
            glm::vec3 inworld(model * pvertices_[i]);
            glm::vec2 from_origin(inworld[0] - origin[0], inworld[1] - origin[1]);
            glm::vec2 dir(glm::normalize(from_origin));

            f32 radius = glm::length(from_origin);

            f32 displacement = amplitud * std::sin(angle * radius + phase);

            pnew_vertices[i][0] = inworld[0] + displacement * dir[0];
            pnew_vertices[i][1] = inworld[1] + displacement * dir[1];
            pnew_vertices[i][2] = 1.0f;
        }
    }

    // Allocate and initialize VBO for vertex positions
    gl::BindBuffer(gl::ARRAY_BUFFER, pvbos_[0]);
    gl::BufferData(gl::ARRAY_BUFFER, sizeof(pnew_vertices[0]) * num_vertices, pnew_vertices, gl::DYNAMIC_DRAW);
    gl::BindBuffer(gl::ARRAY_BUFFER, 0);

    delete [] pnew_vertices;
}

/**
 * @brief Render function
 *
 * @detail GameObject-inherited render function
 *
 * @param program GLSL program handle (to set uniforms)
 * @param model   Model matrix to parent's coordinate system
 * @param view    Camera's view matrix (world to NDC)
 *
 */
template <uint32 SIZEX, uint32 SIZEY>
void DynamicGrid<SIZEX, SIZEY>::render(const GLSLProgram &program, const glm::mat3 & model, const glm::mat3 &view) const
{
    program.setUniform("V", view);
    program.setUniform("color", color_);

    gl::BindVertexArray(vao_);

    // Draw using indices
    gl::DrawElements(gl::LINES, sizeof(pindices_) / sizeof(pindices_[0]), gl::UNSIGNED_INT, 0);

    // Unbind
    gl::BindVertexArray(0);
}


} /* namespace JU */
