/*
 * Collideable.hpp
 *
 *  Created on: Nov 5, 2015
 *      Author: jusabiaga
 */

#ifndef COLLIDEABLE_HPP_
#define COLLIDEABLE_HPP_

#include "../graphics/Mesh2D.hpp"       // Mesh2D

namespace JU
{

// Forward Declarations
template <typename T>
class Shareable;


/**
 * This class defines a collideable object
 */
template <typename T>
class Collideable
{
    public:
        Collideable(Shareable<T>* pshare_boundingarea = nullptr, Shareable<Mesh2D>* pshare_mesh = nullptr);
        virtual ~Collideable();

        const T* getBoundingArea() const;

    private:
        Shareable<T>*      pshare_boundingarea_;    //!< pointer to shared bounding area object
        Shareable<Mesh2D>* pshare_mesh_;            //!< pointer to shared mesh object
};

} /* namespace JU */

#include "Collideable.cpp"

#endif /* COLLIDEABLE_HPP_ */
