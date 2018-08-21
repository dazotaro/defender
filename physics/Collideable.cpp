/*
 * Collideable.cpp
 *
 *  Created on: Nov 5, 2015
 *      Author: jusabiaga
 */

// Local includes
#include "Collideable.hpp"
#include "../core/Singleton.hpp"            // Singleton
#include "../core/ResourceManager.hpp"      // ResourceManager, Shareable

namespace JU
{

/**
 * Non-default constructor\
 *
 * @param pshare_boundingarea (shareable) bounding area object
 * @param pshare_mesh 		  (shareable) mesh
 */
template <typename T>
Collideable::Collideable(Shareable<T>* pshare_boundingarea, Shareable<Mesh2D>* pshare_mesh)
                    : pshare_boundingarea_(pshare_boundingarea), pshare_mesh_(pshare_mesh)
{
}


/**
 * Destructor
 */
template <typename T>
Collideable::~Collideable()
{
    Singleton<ResourceManager<T>>::getInstance()->releaseResource(pshare_boundingarea_);
    Singleton<ResourceManager<Mesh2D>>::getInstance()->releaseResource(pshare_mesh);
}


/**
 * Getter function
 *
 * @return (shareable) bounding area
 */
template <typename T>
const T* Collideable::getBoundingArea() const
{
    return pshare_boundingarea_->pdata_;
}

} /* namespace JU */
