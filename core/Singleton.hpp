/*
 * Singleton.hpp
 *
 *  Created on: Jun 25, 2015
 *      Author: jusabiaga
 */

#ifndef SINGLETON_HPP_
#define SINGLETON_HPP_

namespace JU
{

template <typename T>
class Singleton
{
    private:
        Singleton() {}
        Singleton(const Singleton& rhs) {}
        const Singleton<T>& operator=(const Singleton<T>& rhs);

    public:
        static T* getInstance();

    private:
        static T* instance_;
};

} /* namespace JU */

#include "Singleton.cpp"

#endif /* SINGLETON_HPP_ */
