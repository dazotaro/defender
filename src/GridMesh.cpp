
 /* GridMesh.cpp
 *
 *  Created on: Oct 29, 2015
 *      Author: jusabiaga
 */

// Local includes
#include "GridMesh.hpp"

namespace JU
{

GridMesh::GridMesh(uint32 sizex, uint32 sizey)
{
    const f32 width  = 1.0f;
    const f32 height = 1.0f;
    const f32 xinc =  width / (sizex - 1);
    const f32 yinc = height / (sizey - 1);

    // POSITIONS
    const uint32 num_vertices = sizex * sizey;
    glm::vec2 vertexPositions[num_vertices];

    f32 x = -width / 2.0f;
    uint32 counter = 0;
    for (uint32 i = 0; i < sizex; ++i)
    {
        f32 y = -height / 2.0;
        for (uint32 j = 0; j < sizey; ++j)
        {
            vertexPositions[i*sizey + j][0] = x;
            vertexPositions[i*sizey + j][1] = y;

            y += yinc;
        }
        x += xinc;
    }

    // TEXTURE COORDINATES
    const f32 uinc = 1.0f / (sizex - 1);
    const f32 vinc = 1.0f / (sizey - 1);

    glm::vec2 texCoordinates[sizex * sizey];

    f32 u = 0.0f;
    for (uint32 i = 0; i < sizex; ++i)
    {
        f32 v = 0.0;
        for (uint32 j = 0; j < sizey; ++j)
        {
            texCoordinates[i*sizey + j][0] = u;
            texCoordinates[i*sizey + j][1] = v;

            v += vinc;
        }
        u += uinc;
    }

    // INDICES
    const uint32 num_indices = 2 * ( (sizex-1)*sizey + sizex*(sizey-1) );
    uint32 vertexIndices[num_indices];

    uint32 index = 0;
    for (uint32 i = 0; i < sizex; ++i)
    {
        for (uint32 j = 0; j < sizey; ++j)
        {
            if (i > 0)
            {
                // Line to the WEST vertex
                vertexIndices[index++] = (i-1) * sizey + j;
                vertexIndices[index++] =     i * sizey + j;
            }
            if (j > 0)
            {
                // Line to the NORTH vertex
                vertexIndices[index++] = i * sizey + (j-1);
                vertexIndices[index++] = i * sizey + j;
            }
        }
    }

    setData(vertexPositions, num_vertices, vertexIndices, num_indices, gl::LINE, texCoordinates);
}

GridMesh::~GridMesh()
{
}

} /* namespace JU */
