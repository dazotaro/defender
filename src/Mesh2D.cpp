/*
 * Mesh2D.cpp
 *
 *  Created on: Oct 29, 2015
 *      Author: jusabiaga
 */

// Local includes
#include <cstring>		// std::memcpy
#include "Mesh2D.hpp"

namespace JU
{

Mesh2D::Mesh2D() : pvertices_(nullptr), num_vertices_(0), pindices_(nullptr), num_triangles_(0)
{
}


Mesh2D::Mesh2D(const glm::vec2* pvertices, uint32 num_vertices, const uint32* pindices, uint32 num_triangles)
			: pvertices_(nullptr), num_vertices_(0), pindices_(nullptr), num_triangles_(0)
{
	setData(pvertices, num_vertices, pindices, num_triangles);
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


void Mesh2D::getData(const glm::vec2** pvertices, uint32& num_vertices, const uint32** pindices, uint32& num_triangles) const
{
	*pvertices = pvertices_;
	num_vertices = num_vertices_;

	*pindices = pindices_;
	num_triangles = num_triangles_;
}


void Mesh2D::setData(const glm::vec2* pvertices, JU::uint32 num_vertices, const JU::uint32* pindices, JU::uint32 num_triangles)
{
	delete [] pvertices_;
	num_vertices_ = num_vertices;
	pvertices_ = new glm::vec2[num_vertices_];
	std::memcpy(pvertices_, pvertices, sizeof(*pvertices_) * num_vertices_);

	delete [] pindices_;
	num_triangles_ = num_triangles;
	pindices_ = new uint32[num_triangles_];
	std::memcpy(pindices_, pindices, sizeof(uint32) * num_triangles_);
}


} /* namespace JU */
