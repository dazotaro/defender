/*
 * GridMesh.hpp
 *
 *  Created on: Oct 29, 2015
 *      Author: jusabiaga
 */

#ifndef GRIDMESH_HPP_
#define GRIDMESH_HPP_

// Local includes
#include "../graphics/Mesh2D.hpp"   // Mesh2D
#include "../core/Defs.hpp"         // uint32
// Global includes
#include <string>                   // std::string

namespace JU
{

class GridMesh: public Mesh2D
{
    public:
        GridMesh(uint32 sizex, uint32 sizey);
        virtual ~GridMesh();

    public:
        static std::string getId() { return std::string("/proc/gridmesh"); }
};

} /* namespace JU */

#endif /* GRIDMESH_HPP_ */
