/*
 * TriangleMesh.cpp
 *
 *  Created on: Oct 29, 2015
 *      Author: jusabiaga
 */

// Local includes
#include "TriangleMesh.hpp"

namespace JU
{

TriangleMesh::TriangleMesh()
{
    const glm::vec2 vertexPositions[] =
          { { -0.5f, -0.5f }, // V0
            { 0.5f, -0.5f }, // V1
            { 0.0f, 0.5f }, // V2
            };

    const uint32 vertexIndices[] = {
    // First triangle: upper left
            0, 1, 2 };

    const glm::vec2 textureCoordinates[] =
          { { 0.0f, 0.0f }, // V0
            { 1.0f, 0.0f }, // V1
            { 0.5f, 0.5f }, // V2
            };

    setData(vertexPositions, 3, vertexIndices, 3, gl::TRIANGLES, textureCoordinates);
}

TriangleMesh::~TriangleMesh()
{
}

} /* namespace JU */
