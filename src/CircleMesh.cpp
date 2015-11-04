/*
 * CircleMesh.cpp
 *
 *  Created on: Oct 29, 2015
 *      Author: jusabiaga
 */

// Local includes
#include "CircleMesh.hpp"
#include "../graphics/gl_core_4_2.hpp"		// openGL
// Global includes
#include "cmath"							// std::cos

namespace JU
{

CircleMesh::CircleMesh(uint32 num_vertices)
{
    glm::vec2 vertexPositions[num_vertices];
    const f32 angle_delta = 2.0f * M_PI / num_vertices;
    f32 angle = 0.0f;

    for (uint32 i = 0; i < num_vertices; ++i)
    {
        vertexPositions[i][0] = 0.5f * std::cos(angle);
        vertexPositions[i][1] = 0.5f * std::sin(angle);

        angle += angle_delta;
    }

    uint32 vertexIndices[num_vertices];

    for (uint32 i = 0; i < num_vertices; ++i)
    {
        vertexIndices[i] = i;
    }

    setData(vertexPositions, num_vertices, vertexIndices, num_vertices,
            gl::LINE_LOOP);
}

CircleMesh::~CircleMesh()
{
}

} /* namespace JU */
