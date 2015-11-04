/*
 * TriangleMesh.hpp
 *
 *  Created on: Oct 29, 2015
 *      Author: jusabiaga
 */

#ifndef TRIANGLEMESH_HPP_
#define TRIANGLEMESH_HPP_

// Local includes
#include "../graphics/Mesh2D.hpp"   // Mesh2D
// Global includes
#include <string>                   // std::string

namespace JU
{

class TriangleMesh: public Mesh2D
{
    public:
        TriangleMesh();
        virtual ~TriangleMesh();

    public:
        static std::string getId() { return std::string("/proc/trianglemesh"); }
};

} /* namespace JU */

#endif /* TRIANGLEMESH_HPP_ */
