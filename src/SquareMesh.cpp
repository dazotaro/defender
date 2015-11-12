/*
 * SquareMesh.cpp
 *
 *  Created on: Oct 29, 2015
 *      Author: jusabiaga
 */

// Local includes
#include "SquareMesh.hpp"

namespace JU
{

SquareMesh::SquareMesh()
{
    const glm::vec2 vertexPositions[] =
          { { -0.5f, 0.5f },  // V0
            { -0.5f, -0.5f }, // V1
            { 0.5f, 0.5f },   // V2
            { 0.5f, -0.5f },  // V3
            };

    const glm::vec2 texCoordinates[] =
          { { 0.0f, 1.0f }, // V0
            { 0.0f, 0.0f }, // V1
            { 1.0f, 1.0f }, // V2
            { 1.0f, 0.0f }, // V3
            };

    const uint32 vertexIndices[] = {
    // First triangle: upper left
            0, 1, 2,
            // Second triangle: bottom right
            1, 3, 2, };

    setData(vertexPositions, 4, vertexIndices, 6, gl::TRIANGLES, texCoordinates);
}

SquareMesh::~SquareMesh()
{
}

} /* namespace JU */
