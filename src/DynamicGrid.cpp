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
    gl::VertexAttribPointer(0, 2, gl::FLOAT, gl::FALSE_, 0, 0);

    // Allocate and initialize VBO for vertex indices
    gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, pvbos_[1]);
    gl::BufferData(gl::ELEMENT_ARRAY_BUFFER, sizeof(pindices_), pindices_, gl::STATIC_DRAW);

    // Unbind
    gl::BindBuffer(gl::ARRAY_BUFFER, 0);
    gl::BindVertexArray(0);

    // Physics Simulation
    // ------------------
    // Initialize Velocities and force accumulators
    for (uint32 i = 0; i < SIZEX * SIZEY; ++i)
    {
        pvelocities_[i].x = 0.0f;
        pvelocities_[i].y = 0.0f;
        pforces_[i].x = 0.0f;
        pforces_[i].y = 0.0f;
    }
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
    moveable_.position_[0] = 0.0f;
    moveable_.position_[1] = 0.0f;
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

    glm::mat3 model;
    moveable_.getToParentTransformation(model);

    const f32 ks      = 3.8f;
    const f32 kd      = 0.6f;
    const f32 x_rest  = 1.0f / (SIZEX - 1);
    const f32 y_rest  = 1.0f / (SIZEY - 1);

    // Accumulate Spring Forces
    if (SIZEX > 0 || SIZEY > 0)
    {
        for (JU::uint32 index = 0; index < 2 * ( (SIZEX-1)*SIZEY + SIZEX*(SIZEY-1) ); index += 2)
        {
            glm::vec2 P1toP2 (pvertices_[pindices_[index + 1]] - pvertices_[pindices_[index]]);
            JU::f32 P1toP2distance = glm::length(P1toP2);
            glm::vec2 P1toP2normalized = glm::normalize(P1toP2);

            glm::vec2 V1toV2 (pvelocities_[pindices_[index + 1]] - pvelocities_[pindices_[index]]);

            f32 resting_distance = 0.0f;
            if (pvertices_[pindices_[index + 1]].x == pvertices_[pindices_[index]].y)
                resting_distance = x_rest;
            else
                resting_distance = y_rest;

            glm::vec2 force ((-ks * (P1toP2distance - resting_distance) - kd * V1toV2 * P1toP2normalized) * P1toP2normalized);

            pforces_[pindices_[index + 1]] += force;
            pforces_[pindices_[index]]     -= force;
        }
    }

    // Integration
    for (uint32 i = 0; i < SIZEX * SIZEY; ++i)
    {
        pvertices_[i]   += milliseconds * 0.001f * pvelocities_[i];
        pvelocities_[i] += milliseconds * 0.001f * pforces_[i] / mass_;
    }


    // Allocate and initialize VBO for vertex positions
    gl::BindBuffer(gl::ARRAY_BUFFER, pvbos_[0]);
    gl::BufferData(gl::ARRAY_BUFFER, sizeof(pvertices_), pvertices_, gl::DYNAMIC_DRAW);
    gl::BindBuffer(gl::ARRAY_BUFFER, 0);
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
