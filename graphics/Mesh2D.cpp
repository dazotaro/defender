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

Mesh2D::Mesh2D() : pvertices_(nullptr), num_vertices_(0), pindices_(nullptr), num_indices_(0), draw_mode_(gl::TRIANGLES), ptexcoordinates_(nullptr)
{
}


Mesh2D::Mesh2D(const glm::vec2* pvertices,
               uint32           num_vertices,
               const uint32*    pindices,
               uint32           num_indices,
               const glm::vec2* ptexcoordinates,
               GLenum           draw_mode)
            : pvertices_(nullptr), num_vertices_(0), pindices_(nullptr), num_indices_(0), draw_mode_(draw_mode), ptexcoordinates_(nullptr)
{
    setData(pvertices, num_vertices, pindices, num_indices, draw_mode, ptexcoordinates);
}


Mesh2D::~Mesh2D()
{
    delete [] pvertices_;
    delete [] pindices_;
}


/**
* @brief Get vertex position data (const version)
*
* @detail Get vertex position data.
*
* @param pvertices      The address of the pointer to the array of vertices
* @param num_vertices   Number of vertices in the mesh
*
*/
void Mesh2D::getVertexCoordinates(const glm::vec2* & pvertices, uint32& num_vertices) const
{
    pvertices = pvertices_;
    num_vertices = num_vertices_;
}



/**
* @brief Get vertex position data (non-const version)
*
* @detail Get vertex position data. Non-const version for actually modifying this data.
*
* @param pvertices      The address of the pointer to the array of vertices
* @param num_vertices   Number of vertices in the mesh
*
*/
void Mesh2D::getVertexCoordinates(glm::vec2* & pvertices, uint32& num_vertices)
{
    pvertices = pvertices_;
    num_vertices = num_vertices_;
}



void Mesh2D::getData(const glm::vec2** pvertices,
                     uint32&           num_vertices,
                     const uint32**    pindices,
                     uint32&           num_indices,
                     GLenum&           draw_mode,
                     const glm::vec2** ptexcoordinates) const
{
    *pvertices = pvertices_;
    num_vertices = num_vertices_;

    *pindices = pindices_;
    num_indices = num_indices_;

    *ptexcoordinates = ptexcoordinates_;

    draw_mode = draw_mode_;
}



/**
* @brief Set the vertex positions
*
* @detail Update the vertex data. It assumes that the number of vertices is already set and is
*         equal to num_vertices_
*
* @param pvertices Vertex coordinates
*
*/
void Mesh2D::updateVertexCoordinates(const glm::vec2* pvertices)
{
    std::memcpy(pvertices_, pvertices, num_vertices_* sizeof(num_vertices_));
}


void Mesh2D::setData(const glm::vec2* pvertices,
                     uint32           num_vertices,
                     const uint32*    pindices,
                     uint32           num_indices,
                     GLenum           draw_mode,
                     const glm::vec2* ptexcoordinates)
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
