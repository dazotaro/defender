/*
 * SkylineMesh.hpp
 *
 *  Created on: Oct 29, 2015
 *      Author: jusabiaga
 */

#ifndef SKYLINEMESH_HPP_
#define SKYLINEMESH_HPP_

// Local includes
#include "../graphics/Mesh2D.hpp"	// Mesh2D
// Global includes
#include <string>                   // std::string

namespace JU
{

class SkylineMesh: public Mesh2D
{
    public:
        SkylineMesh();
        virtual ~SkylineMesh();

    public:
        static std::string getId() { return std::string("/proc/terrainmesh"); }
};

} /* namespace JU */

#endif /* SKYLINEMESH_HPP_ */
