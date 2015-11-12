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
    const f32 radius = 0.5f;
    f32 angle = 0.0f;

    for (uint32 i = 0; i < num_vertices; ++i)
    {
        vertexPositions[i][0] = radius * std::cos(angle);
        vertexPositions[i][1] = radius * std::sin(angle);

        angle += angle_delta;
    }

    uint32 vertexIndices[num_vertices];

    for (uint32 i = 0; i < num_vertices; ++i)
    {
        vertexIndices[i] = i;
    }

    // Texture Coordinates
    glm::vec2 textureCoordinates[num_vertices];
    angle = 0.0f;
    for (uint32 i = 0; i < num_vertices; ++i)
    {
        textureCoordinates[i][0] = radius * std::cos(angle) + radius;
        textureCoordinates[i][1] = radius * std::sin(angle) + radius;

        angle += angle_delta;
    }

    setData(vertexPositions, num_vertices, vertexIndices, num_vertices, gl::LINE_LOOP, textureCoordinates);
}

CircleMesh::~CircleMesh()
{
}

} /* namespace JU */
