/*
 * DynamicGrid.cpp
 *
 *  Created on: Nov 12, 2015
 *      Author: jusabiaga
 */

#include "DynamicGrid.hpp"
#include "../graphics/GLMesh2DInstance.hpp" // GLMesh2DInstance
#include "../graphics/GLMesh2D.hpp"         // GLMesh2D
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
DynamicGrid::DynamicGrid(Moveable2D moveable, uint32 sizex, uint32 sizey, const glm::vec4& color)
                : moveable_(moveable), mesh_(sizex, sizey), color_(color)
{
    // GLMesh2D
    // -------------
    glmesh_.transferDataGPU(mesh_, gl::DYNAMIC_DRAW);
}

/**
 * @brief Destructor
 *
 */
DynamicGrid::~DynamicGrid()
{
    glmesh_.releaseDataGPU();
}


/**
 * @brief Update function
 *
 * @param milliseconds  Time elapsed since the last call (in milliseconds)
 *
 */
void DynamicGrid::update(f32 milliseconds)
{
    static f32 elapsed_time = milliseconds;

    elapsed_time += milliseconds;

    Mesh2D tmpmesh(mesh_);

    glm::vec2* pvertices = nullptr;
    uint32 num_vertices = 0;
    tmpmesh.getVertexCoordinates(pvertices, num_vertices);

    if (num_vertices)
    {
        glm::vec2 origin(0.0f, 0.0f);
        f32 amplitud = 0.01f;
        const f32 freq = 8.0f;
        f32 angle = 2.0f * M_PI * freq;
        f32 phase = elapsed_time * 2.0f * M_PI * 0.001f;

        for (uint32 i = 0; i < num_vertices; ++i)
        {
            glm::vec2 vertex(pvertices[i]);
            glm::vec2 dir(glm::normalize(vertex));

            f32 radius = std::sqrt((vertex[0] - origin[0])*(vertex[0] - origin[0]) + (vertex[1] - origin[1])*(vertex[1] - origin[1]));

            f32 displacement = amplitud * std::sin(angle * radius + phase);
            vertex += displacement * dir;

            pvertices[i] = vertex;
        }
    }

    glmesh_.releaseDataGPU();
    glmesh_.transferDataGPU(tmpmesh, gl::DYNAMIC_DRAW);
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
void DynamicGrid::render(const GLSLProgram &program, const glm::mat3 & model, const glm::mat3 &view) const
{
    glm::mat3 toparent;
    moveable_.getToParentTransformation(toparent);

    glm::mat3 MV = view * model * toparent;

    program.setUniform("MV", MV);
    program.setUniform("color", color_);

    glmesh_.render();
}


} /* namespace JU */
