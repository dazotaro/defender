/*
 * SquareMesh.hpp
 *
 *  Created on: Oct 29, 2015
 *      Author: jusabiaga
 */

#ifndef SQUAREMESH_HPP_
#define SQUAREMESH_HPP_

// Local includes
#include "../graphics/Mesh2D.hpp"   // Mesh2D
// Global includes
#include <string>                   // std::string

namespace JU
{

class SquareMesh: public Mesh2D
{
    public:
        SquareMesh();
        virtual ~SquareMesh();

    public:
        static std::string getId() { return std::string("/proc/squaremesh"); }
};

} /* namespace JU */

#endif /* SQUAREMESH_HPP_ */
