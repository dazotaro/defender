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
		Mesh2D(const glm::vec2* pvertices, uint32 num_vertices, const uint32* pindices, uint32 num_indices);
		virtual ~Mesh2D();

		// Getter
		void getVertices(const glm::vec2** pvertices, uint32& num_vertices) const;
		void getData(const glm::vec2** pvertices, uint32& num_vertices, const uint32** pindices, uint32& num_indices) const;

		// Setter
		void setData(const glm::vec2* pvertices, uint32 num_vertices, const uint32* pindices, uint32 num_indices);

	protected:
		glm::vec2* 	pvertices_;
		uint32  	num_vertices_;
		uint32*		pindices_;
		uint32		num_indices_;
};

} /* namespace JU */

#endif /* MESH2D_HPP_ */
