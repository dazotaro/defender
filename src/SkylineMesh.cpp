/*
 * SkylineMesh.cpp
 *
 *  Created on: Oct 29, 2015
 *      Author: jusabiaga
 */

// Local includes
#include "SkylineMesh.hpp"
#include "../graphics/gl_core_4_2.hpp"		// openGL
// Global includes
#include "cmath"							// std::cos

namespace JU
{

SkylineMesh::SkylineMesh()
{
    const uint32 num_vertices = 5;
    glm::vec2 vertexPositions[num_vertices];

    vertexPositions[0][0] = -5.0f;
    vertexPositions[0][1] = 0.0f;
    vertexPositions[1][0] = -2.5f;
    vertexPositions[1][1] = -2.0f;
    vertexPositions[2][0] = 0.0f;
    vertexPositions[2][1] = 3.0f;
    vertexPositions[3][0] = 2.5f;
    vertexPositions[3][1] = -1.0f;
    vertexPositions[4][0] = 5.0f;
    vertexPositions[4][1] = 0.0f;

    uint32 vertexIndices[num_vertices];

    for (uint32 i = 0; i < num_vertices; ++i)
    {
        vertexIndices[i] = i;
    }

    setData(vertexPositions, num_vertices, vertexIndices, num_vertices,
            gl::LINE_STRIP);
}

SkylineMesh::~SkylineMesh()
{
}

} /* namespace JU */
