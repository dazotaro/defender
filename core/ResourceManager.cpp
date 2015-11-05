/*
 * ResourceManager.cpp
 *
 *  Created on: Nov 1, 2015
 *      Author: jusabiaga
 */

namespace JU
{

/**
* @brief Default constructor
*/
template <typename T>
ResourceManager<T>::ResourceManager()
{
    std::printf("%s\n", __PRETTY_FUNCTION__);
}


/**
* @brief Destructor
*/
template <typename T>
ResourceManager<T>::~ResourceManager()
{
    std::printf("%s\n", __PRETTY_FUNCTION__);

    typename ResourceHashMap::iterator iter;
    for(iter = resource_manager_hm_.begin(); iter != resource_manager_hm_.end(); ++iter)
    {
        delete iter->second.second;
    }

    resource_manager_hm_.clear();
}


/**
* @brief Find a Resource in the hash-map
*
* @param id Id of the resource
*
* @return True/False if found/not-found
*/
template <typename T>
bool ResourceManager<T>::findResource(const std::string& id) const
{
    if (resource_manager_hm_.find(id) == resource_manager_hm_.end())
        return false;

    return true;
}


/**
* @brief Add a Resource to the hash-map
*
* @detail This function assumes that the resource does not exist, so it should be
* called after findResource.
*
* @param id         Id of the resource
* @param p_resource Pointer to the T to be added
*
* @return True/False if found/not-found
*/
template <typename T>
Shareable<T>* ResourceManager<T>::addResource(const std::string& id, T* pdata)
{
    auto iter = resource_manager_hm_.find(id);

    // If a reasource with this type and id is already in the hash map
    if (iter != resource_manager_hm_.end())
    {
        std::printf("Resource with that name already exits");

        return iter->second.second;
    }

    Shareable<T>* presource (new Shareable<T>(id, pdata));

    resource_manager_hm_.insert(std::make_pair(id, std::make_pair(1, presource)));

    return presource;
}


/**
* @brief Get a resource
*
* @param id Id of the resource
*
* @return Pointer to T identified by id if resource present, 'nullptr' otherwise
*/
template <typename T>
Shareable<T>* ResourceManager<T>::getResource(const std::string& id) const
{
    typename ResourceHashMap::const_iterator iter = resource_manager_hm_.find(id);

    if (iter != resource_manager_hm_.end())
    {
        return iter->second.second;
    }

    return nullptr;
}


/**
* @brief Reference an existing resource
*
* @param id         Id of the resource
*
* @return Pointer to Shareable identified by id if resource present, 'nullptr' otherwise
*/
template <typename T>
Shareable<T>* ResourceManager<T>::referenceResource(const std::string& id)
{
    typename ResourceHashMap::iterator iter = resource_manager_hm_.find(id);

    if (iter != resource_manager_hm_.end())
    {
        iter->second.first++;

        std::printf("%s: %s reference count = %i\n", __PRETTY_FUNCTION__,
                                                iter->first.c_str(),
                                                iter->second.first);
        return iter->second.second;
    }

    return nullptr;
}


/**
* @brief Release a resource
*
* @param id         Id of the resource
*
* @return True/False if found/not-found
*/
template <typename T>
bool ResourceManager<T>::releaseResource(Shareable<T>* presource)
{
    typename ResourceHashMap::iterator iter = resource_manager_hm_.find(presource->id_);

    if (iter == resource_manager_hm_.end())
        return false;

    std::printf("%s: %s reference count = %i\n", __PRETTY_FUNCTION__,
                                                iter->first.c_str(),
                                                iter->second.first);

    if(--iter->second.first == 0)
    {
        // Delete Resource
        delete iter->second.second;
        // Remove Resource entry in Hash Map
        resource_manager_hm_.erase(iter);
    }

    return true;
}


} /* namespace JU */
