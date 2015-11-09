/*
 * Mesh2D.cpp
 *
 *  Created on: Oct 29, 2015
 *      Author: jusabiaga
 */

// Local includes
#include <cstring>      // std::memcpy
#include "Mesh2D.hpp"

namespace JU
{

Mesh2D::Mesh2D() : pvertices_(nullptr), num_vertices_(0), pindices_(nullptr), num_indices_(0), ptexcoordinates_(nullptr), draw_mode_(gl::TRIANGLES)
{
}


Mesh2D::Mesh2D(const glm::vec2* pvertices,
               uint32           num_vertices,
               const uint32*    pindices,
               uint32           num_indices,
               const glm::vec2* ptexcoordinates,
               GLenum           draw_mode)
            : pvertices_(nullptr), num_vertices_(0), pindices_(nullptr), num_indices_(0), ptexcoordinates_(nullptr), draw_mode_(draw_mode)
{
    setData(pvertices, num_vertices, pindices, num_indices, ptexcoordinates, draw_mode);
}


Mesh2D::~Mesh2D()
{
    delete [] pvertices_;
    delete [] pindices_;
}


void Mesh2D::getVertices(const glm::vec2** pvertices, uint32& num_vertices) const
{
    *pvertices = pvertices_;
    num_vertices = num_vertices_;
}


void Mesh2D::getData(const glm::vec2** pvertices,
                     uint32&           num_vertices,
                     const uint32**    pindices,
                     uint32&           num_indices,
                     const glm::vec2** ptexcoordinates,
                     GLenum&           draw_mode) const
{
    *pvertices = pvertices_;
    num_vertices = num_vertices_;

    *pindices = pindices_;
    num_indices = num_indices_;

    *ptexcoordinates = ptexcoordinates_;

    draw_mode = draw_mode_;
}


void Mesh2D::setData(const glm::vec2* pvertices,
                     uint32           num_vertices,
                     const uint32*    pindices,
                     uint32           num_indices,
                     const glm::vec2* ptexcoordinates,
                     GLenum           draw_mode)
{
    delete [] pvertices_;
    num_vertices_ = num_vertices;
    pvertices_ = new glm::vec2[num_vertices_];
    std::memcpy(pvertices_, pvertices, sizeof(*pvertices_) * num_vertices_);

    delete [] pindices_;
    num_indices_ = num_indices;
    pindices_ = new uint32[num_indices_];
    std::memcpy(pindices_, pindices, sizeof(uint32) * num_indices_);

    if (ptexcoordinates)
    {
        delete [] ptexcoordinates_;
        ptexcoordinates_ = new glm::vec2[num_vertices];
        std::memcpy(ptexcoordinates_, ptexcoordinates, sizeof(*ptexcoordinates) * num_vertices);
    }

    draw_mode_ = draw_mode;
}


} /* namespace JU */
