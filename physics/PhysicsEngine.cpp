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
#include "../core/Moveable2D.hpp"	// Moveable2D
// Global includes
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
    uint32 num_bodies = mrigid_bodies_.size();
    BoundingCircle* pcircles = new BoundingCircle[num_bodies];

    uint32 i = 0;
    for (RigidBodyPointerMapIter iter = mrigid_bodies_.begin();
            iter != mrigid_bodies_.end(); ++iter)
    {
        RigidBody* pbody = iter->second;
        glm::mat3 model;
        pbody->getMoveable()->getToParentTransformation(model);
        const BoundingCircle* pcircle = pbody->getBoundingArea();
        glm::vec3 new_center = model
                * glm::vec3(pcircle->center_[0], pcircle->center_[1], 1.0f);
        pcircles[i].center_ = glm::vec2(new_center[0], new_center[1]);
        pcircles[i].radius_ = pcircle->radius_
                * glm::max(pbody->getMoveable()->scale_[0],
                        pbody->getMoveable()->scale_[1]);

        ++i;
    }

    // Brute Force all-pairs collision test
    for (uint32 i = 0; i < num_bodies - 1; ++i)
    {
        for (uint32 j = i + 1; j < num_bodies; ++j)
        {
            if (testCollision(pcircles[i], pcircles[j]))
            {
                std::printf("Collision occurred\n");
            }
        }
    }

    delete[] pcircles;
}

void PhysicsEngine::addRigidBody(const std::string& name,
        RigidBody* prigid_body)
{
    if (mrigid_bodies_.find(name) == mrigid_bodies_.end())
    {
        mrigid_bodies_[name] = prigid_body;
    }
}

void PhysicsEngine::removeRigidBody(const std::string& name)
{
    mrigid_bodies_.erase(name);
}

} /* namespace JU */
