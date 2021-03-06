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

static glm::vec2 dampedSpringForce(const glm::vec2& vtx0, const glm::vec2& vtx1,
                       const glm::vec2& vel0, const glm::vec2& vel1,
                       f32 resting_distance, f32 ks, f32 kd)
{
    glm::vec2 P1toP2 (vtx1 - vtx0);
    JU::f32 P1toP2distance = glm::length(P1toP2);
    glm::vec2 P1toP2normalized = glm::normalize(P1toP2);

    glm::vec2 V1toV2 (vel1 - vel0);

    return glm::vec2((-ks * (P1toP2distance - resting_distance) - kd * V1toV2 * P1toP2normalized) * P1toP2normalized);
}

/**
 * @brief Non-default constructor
 *
 * @param posx  X coordinate of position
 * @param posy  Y coordinate of position
 * @param angle Angle of orientation in radians
 *
 */
template <uint32 SIZEX, uint32 SIZEY>
DynamicGrid<SIZEX, SIZEY>::DynamicGrid(Moveable2D moveable, f32 mass, f32 ks, f32 kd, const glm::vec4& color)
                : ks_(ks), kd_(kd), x_rest_(1.0f / (SIZEX - 1)), y_rest_(1.0f / (SIZEY - 1)), vao_(0), color_(color)
{
    const f32 width  = 1.0f;
    const f32 height = 1.0f;
    const f32 xinc =  width / (SIZEX - 1);
    const f32 yinc = height / (SIZEY - 1);

    glm::mat3 model;
    moveable.getToParentTransformation(model);

    x_rest_ *= moveable.scale_.x;
    y_rest_ *= moveable.scale_.y;

    // POSITIONS
    f32 x = -width / 2.0f;
    for (uint32 i = 0; i < SIZEX; ++i)
    {
        f32 y = -height / 2.0;
        for (uint32 j = 0; j < SIZEY; ++j)
        {
            glm::vec3 vtx_world = model * glm::vec3(x, y, 1.0f);
            // Transform positions from local to world coordinate
            pvertices_[i][j].x = vtx_world.x;
            pvertices_[i][j].y = vtx_world.y;

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
    memset(pvelocities_, 0, sizeof(pvelocities_));
    memset(pforces_,     0, sizeof(pforces_));

    for (uint32 i = 0; i < SIZEX; ++i)
    {
        for (uint32 j = 0; j < SIZEY; ++j)
        {
            if (i == 0 || j == 0 || i == (SIZEX - 1) || j == (SIZEY - 1))
                pmass_[i][j] = 0.0f;
            else
                pmass_[i][j] = mass;
        }
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
 * @brief Get the dimensions (X, Y) of the grid
 *
 * @param sizex      Number of particles on X direction
 * @param sizey      Number of particles on Y direction
 *
 */
template <uint32 SIZEX, uint32 SIZEY>
void DynamicGrid<SIZEX, SIZEY>::getDimensions(uint32& sizex, uint32& sizey) const
{
    sizex = SIZEX;
    sizey = SIZEY;
}


/**
 * @brief Get the positions of all particles in the grid
 *
 * @param ppositions Pointer to pointer to vec2 to the positions
 *
 */
template <uint32 SIZEX, uint32 SIZEY>
void DynamicGrid<SIZEX, SIZEY>::getPositions(const glm::vec2** ppositions) const
{
    *ppositions = &pvertices_[0][0];
}


/**
* @brief Get the velocities of all particles in the grid
*
* @param pvelocities Pointer to pointer to vec2 to velocities
*
*/
template <uint32 SIZEX, uint32 SIZEY>
void DynamicGrid<SIZEX, SIZEY>::getVelocities(const glm::vec2** pvelocities) const
{
   *pvelocities = &pvelocities_[0][0];
}


/**
 * @brief Get the resting distance between particles
 *
 * @param xrest Resting distance on X direction
 * @param yrest Resting distance on Y direction
 *
 */
template <uint32 SIZEX, uint32 SIZEY>
void DynamicGrid<SIZEX, SIZEY>::getRestDistances(f32& xrest, f32& yrest) const
{
    xrest = x_rest_;
    yrest = y_rest_;
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
    // Reset force accumulators
    memset(pforces_, 0, sizeof(pforces_));

    // Accumulate Spring Forces
    for (uint32 i = 0; i < SIZEX; ++i)
    {
        for (uint32 j = 0; j < SIZEY; ++j)
        {
            if (i > 0)
            {
                // Line to the WEST vertex
                // -----------------------
                uint32 row0 = i,     col0 = j;
                uint32 row1 = i - 1, col1 = j;
                glm::vec2 force = dampedSpringForce(pvertices_[row0][col0], pvertices_[row1][col1],
                                                    pvelocities_[row0][col0], pvelocities_[row1][col1],
                                                    x_rest_, ks_, kd_);
                pforces_[row1][col1] += force;
                pforces_[row0][col0] -= force;
            }
            if (i > 1)
            {
                // Line to the WEST-WEST vertex
                // -----------------------
                uint32 row0 = i,     col0 = j;
                uint32 row1 = i - 2, col1 = j;
                glm::vec2 force = dampedSpringForce(pvertices_[row0][col0], pvertices_[row1][col1],
                                                    pvelocities_[row0][col0], pvelocities_[row1][col1],
                                                    2.0f * x_rest_, ks_ * 1.5f, kd_);
                pforces_[row1][col1] += force;
                pforces_[row0][col0] -= force;
            }
            if (j > 0)
            {
                // Line to the NORTH vertex
                // -----------------------
                uint32 row0 = i, col0 = j;
                uint32 row1 = i, col1 = j - 1;
                glm::vec2 force = dampedSpringForce(pvertices_[row0][col0], pvertices_[row1][col1],
                                                    pvelocities_[row0][col0], pvelocities_[row1][col1],
                                                    y_rest_, ks_, kd_);
                pforces_[row1][col1] += force;
                pforces_[row0][col0] -= force;
            }
            if (j > 1)
            {
                // Line to the NORTH-NORTH vertex
                // -----------------------
                uint32 row0 = i, col0 = j;
                uint32 row1 = i, col1 = j - 2;
                glm::vec2 force = dampedSpringForce(pvertices_[row0][col0], pvertices_[row1][col1],
                                                    pvelocities_[row0][col0], pvelocities_[row1][col1],
                                                    2.0f * y_rest_, ks_ * 1.5f, kd_);
                pforces_[row1][col1] += force;
                pforces_[row0][col0] -= force;
            }
        }
    }


    // Accumulate repulsive forces due to spaceships
    for (uint32 i = 0; i < SIZEX; ++i)
    {
        for (uint32 j = 0; j < SIZEY; ++j)
        {
            if (i != 0 && j != 0 && i != (SIZEX - 1) && j != (SIZEY - 1))
            {
                for (uint32 k = 0; k < num_forces; ++k)
                {
                    glm::vec2 from_force(pvertices_[i][j] - force_locations[k]);
                    f32 distance = glm::length(from_force);
                    distance = (distance < x_rest_ * 0.3f ? x_rest_ * 0.3f : distance);
                    pforces_[i][j] += 5.0f / (distance * distance) * glm::normalize(from_force);
                }
            }
        }
    }

    // Integration
    for (uint32 i = 0; i < SIZEX; ++i)
    {
        for (uint32 j = 0; j < SIZEY; ++j)
        {
            if (i != 0 && j != 0 && i != (SIZEX - 1) && j != (SIZEY - 1))
            {
                pvertices_[i][j] += milliseconds * 0.001f * pvelocities_[i][j];
                pvelocities_[i][j] += milliseconds * 0.001f * pforces_[i][j] / pmass_[i][j];
            }
        }
    }
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

    // Allocate and initialize VBO for vertex positions
    gl::BindBuffer(gl::ARRAY_BUFFER, pvbos_[0]);
    gl::BufferData(gl::ARRAY_BUFFER, sizeof(pvertices_), pvertices_, gl::DYNAMIC_DRAW);
    gl::BindBuffer(gl::ARRAY_BUFFER, 0);

    // Draw using indices
    gl::DrawElements(gl::LINES, sizeof(pindices_) / sizeof(pindices_[0]), gl::UNSIGNED_INT, 0);

    // Unbind
    gl::BindVertexArray(0);
}


} /* namespace JU */
