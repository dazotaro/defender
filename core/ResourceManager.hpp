/*
 * ResourceManager.hpp
 *
 *  Created on: Nov 1, 2015
 *      Author: jusabiaga
 */

#ifndef RESOURCEMANAGER_HPP_
#define RESOURCEMANAGER_HPP_

// Local includes
#include "Singleton.hpp"    // Singleton
// Global includes
#include <string>           // std::string
#include <unordered_map>    // unordered_map

namespace JU
{

/**
 * Programming exercises that implement smart pointers
 * \todo replace it with actual C++11 smart pointers
 */
template<typename T>
class Shareable
{
    public:
        Shareable(const std::string& id, T* pdata) :
                id_(id), pdata_(pdata)
        {
        }
        ~Shareable()
        {
            delete pdata_;
        }

        const std::string id_;
        T* const pdata_;
};

/**
 * Resource Manager
 */
template<typename T>
class ResourceManager
{
    public:

        template <typename U>
        friend class Singleton;
        /*
        static ResourceManager& getInstance()
        {
            static ResourceManager singleton;

            return singleton;
        }
        */


        ~ResourceManager();

    protected:
        ResourceManager();
        ResourceManager(const ResourceManager& manager) {}
        ResourceManager& operator=(const ResourceManager& manager);

    public:
        bool findResource(const std::string& id) const;
        Shareable<T>* addResource(const std::string& id, T* pdata);
        Shareable<T>* getResource(const std::string& id) const;
        Shareable<T>* referenceResource(const std::string& id);
        bool releaseResource(Shareable<T>* presource);

    private:
        // Typedefs
        typedef std::pair<unsigned, Shareable<T>*> ShareableResource;   //!< First = reference counter; second = Pointer to shareable data
        typedef std::unordered_map<std::string, ShareableResource> ResourceHashMap;

        // Data Members
        ResourceHashMap resource_manager_hm_; //!< Hash-Map to store the pointers to Resources based on their ids
};

} /* namespace JU */

#include "ResourceManager.cpp"

#endif /* RESOURCEMANAGER_HPP_ */
