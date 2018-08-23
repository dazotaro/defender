/*
 * Singleton.cpp
 *
 *  Created on: Jun 25, 2015
 *      Author: jusabiaga
 */

#include "Singleton.hpp"

namespace JU
{

template <typename T>
T* Singleton<T>::instance_ = nullptr;


/**
 * Destructor
 */
template <typename T>
Singleton<T>::~Singleton()
{
    delete instance_;
}


/**
 * Get singleton
 *
 * @return Instance of singleton
 */
template <typename T>
T* Singleton<T>::getInstance()
{
    if(instance_ == nullptr)
        instance_ = new T;

    return instance_;
}


} /* namespace JU */
