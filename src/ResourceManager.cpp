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
}


template <typename T>
ResourceManager<T>::~ResourceManager()
{
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
* @param id	Id of the resource
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
* @param id			Id of the resource
* @param p_resource	Pointer to the T to be added
*
* @return True/False if found/not-found
*/
template <typename T>
bool ResourceManager<T>::addResource(const std::string& id, T* presource)
{
	if (resource_manager_hm_.find(id) != resource_manager_hm_.end())
		return false;

	resource_manager_hm_.insert(std::make_pair(id, std::make_pair(0, presource)));

	return true;
}


/**
* @brief Get a resource
*
* @param id	Id of the resource
*
* @return Pointer to T identified by id if resource present, 'nullptr' otherwise
*/
template <typename T>
T* ResourceManager<T>::getResource(const std::string& id) const
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
* @param id			Id of the resource
*
* @return Pointer to T identified by id if resource present, 'nullptr' otherwise
*/
template <typename T>
T* ResourceManager<T>::referenceResource(const std::string& id)
{
	typename ResourceHashMap::iterator iter = resource_manager_hm_.find(id);

	if (iter != resource_manager_hm_.end())
	{
		iter->second.first++;

		return iter->second.second;
	}

	return nullptr;
}


/**
* @brief Release a resource
*
* @param id			Id of the resource
*
* @return True/False if found/not-found
*/
template <typename T>
bool ResourceManager<T>::releaseResource(const std::string& id)
{
	typename ResourceHashMap::const_iterator iter = resource_manager_hm_.find(id);

	if (iter == resource_manager_hm_.end())
		return false;

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