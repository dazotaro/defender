/*
 * Mesh.hpp
 *
 *  Created on: Oct 29, 2015
 *      Author: jusabiaga
 */

#ifndef MESH2D_HPP_
#define MESH2D_HPP_

#include "Defs.hpp"			// JU::uint32
#include <glm/glm.hpp>		// glm::vec2


namespace JU
{

class Mesh2D
{
	public:
		Mesh2D();
		Mesh2D(const glm::vec2* pvertices, JU::uint32 num_vertices, const JU::uint32* pindices, JU::uint32 num_triangles);
		virtual ~Mesh2D();

		// Getter
		void getVertices(const glm::vec2** pvertices, JU::uint32& num_vertices) const;
		void getData(const glm::vec2** pvertices, JU::uint32& num_vertices, const JU::uint32** pindices, JU::uint32& num_triangles) const;

		// Setter
		void setData(const glm::vec2* pvertices, JU::uint32 num_vertices, const JU::uint32* pindices, JU::uint32 num_triangles);

	protected:
		glm::vec2* 	pvertices_;
		JU::uint32  num_vertices_;
		JU::uint32*	pindices_;
		JU::uint32	num_triangles_;
};

} /* namespace JU */

#endif /* MESH2D_HPP_ */
