/*
 * PhysicsEngine.hpp
 *
 *  Created on: Oct 30, 2015
 *      Author: jusabiaga
 */

#ifndef PHYSICSENGINE_HPP_
#define PHYSICSENGINE_HPP_

// Local includes
#include "../src/Defs.hpp"		// uint32
// Global includes
#include <map>					// std::map
#include <string>				// std::string

namespace JU
{

// Forward Declarations
class RigidBody;

class PhysicsEngine
{
	public:
		PhysicsEngine();
		virtual ~PhysicsEngine();

		void init();

		void updateCollisions(uint32 milliseconds);
		void addRigidBody(const std::string& name, RigidBody* prigid_body);
		void removeRigidBody(const std::string& name);

	private:
		typedef std::map<std::string, RigidBody*> RigidBodyPointerMap;
		typedef RigidBodyPointerMap::iterator     RigidBodyPointerMapIter;
		std::map<std::string, RigidBody*>	mrigid_bodies_;
};

} /* namespace JU */

#endif /* PHYSICSENGINE_HPP_ */
