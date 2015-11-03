/*
 * CircleMesh.hpp
 *
 *  Created on: Oct 29, 2015
 *      Author: jusabiaga
 */

#ifndef CIRCLEMESH_HPP_
#define CIRCLEMESH_HPP_

#include "../graphics/Mesh2D.hpp"	// Mesh2D

namespace JU
{

class CircleMesh : public Mesh2D
{
	public:
		CircleMesh(uint32 num_vertices);
		virtual ~CircleMesh();
};

} /* namespace JU */

#endif /* CIRCLEMESH_HPP_ */
