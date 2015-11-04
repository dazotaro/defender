/*
 * SquareMesh.hpp
 *
 *  Created on: Oct 29, 2015
 *      Author: jusabiaga
 */

#ifndef SQUAREMESH_HPP_
#define SQUAREMESH_HPP_

#include "../graphics/Mesh2D.hpp"	// Mesh2D

namespace JU
{

class SquareMesh: public Mesh2D
{
    public:
        SquareMesh();
        virtual ~SquareMesh();
};

} /* namespace JU */

#endif /* SQUAREMESH_HPP_ */
