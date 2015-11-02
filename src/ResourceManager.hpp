/*
 * ResourceManager.hpp
 *
 *  Created on: Nov 1, 2015
 *      Author: jusabiaga
 */

#ifndef RESOURCEMANAGER_HPP_
#define RESOURCEMANAGER_HPP_

// Local includes
#include "Singleton.hpp"	// Singleton
// Global includes
#include <string>			// std::string
#include <unordered_map>	// unordered_map

namespace JU
{


template <typename T>
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
		bool addResource(const std::string& id, T* presource);
		T* getResource(const std::string& id) const;
		T* referenceResource(const std::string& id);
		bool releaseResource(const std::string& id);

	private:
		// Typedefs
		typedef std::unordered_map<std::string, std::pair<unsigned, T*> > ResourceHashMap;

		// Data Members
		ResourceHashMap resource_manager_hm_; //!< Hash-Map to store the pointers to Resources based on their ids
};


} /* namespace JU */

#include "ResourceManager.cpp"

#endif /* RESOURCEMANAGER_HPP_ */
