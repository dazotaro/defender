/*
 * TriangleMesh.hpp
 *
 *  Created on: Oct 29, 2015
 *      Author: jusabiaga
 */

#ifndef TRIANGLEMESH_HPP_
#define TRIANGLEMESH_HPP_

#include "Mesh2D.hpp"	// Mesh2D

namespace JU
{

class TriangleMesh : public Mesh2D
{
	public:
		TriangleMesh();
		virtual ~TriangleMesh();
};

} /* namespace JU */

#endif /* TRIANGLEMESH_HPP_ */
