/*
 * PhysicsEngine.cpp
 *
 *  Created on: Oct 30, 2015
 *      Author: jusabiaga
 */

// Local includes
#include "PhysicsEngine.hpp"
#include "RigidBody.hpp"			// RigidBody
#include "Geometry.hpp"				// testCollision
#include "../src/Moveable2D.hpp"	// Moveable2D
#include <glm/glm.hpp>				// mat3

namespace JU
{

PhysicsEngine::PhysicsEngine()
{
	// TODO Auto-generated constructor stub

}

PhysicsEngine::~PhysicsEngine()
{
	// TODO Auto-generated destructor stub
}


void PhysicsEngine::init()
{
}


void PhysicsEngine::updateCollisions(uint32 milliseconds)
{
	// Brute Force all-pairs collision test
	for (RigidBodyPointerMapIter iter1 = mrigid_bodies_.begin(); iter1 != mrigid_bodies_.end(); ++iter1)
	{
		for (RigidBodyPointerMapIter iter2 = iter1, ++iter2; iter2 != mrigid_bodies_.end(); ++iter2)
		{
			glm::mat3 model1, model2;
			iter1->second->getMoveable()->getToParentTransformation(model1);
		}
	}
}


void PhysicsEngine::addRigidBody(const std::string& name, RigidBody* prigid_body)
{
	if (!mrigid_bodies_.find(name))
	{
		mrigid_bodies_[name] = prigid_body;
	}
}


void PhysicsEngine::removeRigidBody(const std::string& name)
{
	mrigid_bodies_.erase(name);
}



} /* namespace JU */
