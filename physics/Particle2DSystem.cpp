/*
 * Particle2DSystem.cpp
 *
 *  Created on: Jan 24, 2014
 *      Author: dazotaro
 */

// Local includes
#include "Force2D.hpp"			// JU::Force2D
#include "Particle2D.hpp"			// JU::Particle2D
#include "Particle2DSystem.hpp"	// JU::Particle2DSystem

namespace JU
{

/**
* Constructor
*/
Particle2DSystem::Particle2DSystem(const Moveable2D &moveable)
						: moveable_(moveable), num_particles_(0), particle_id_(0), force_id_(0)
{
}



/**
* Destructor
*
* \note do we need to check whether the iterator is pointing to NULL
*/
Particle2DSystem::~Particle2DSystem()
{
	// FORCE2DS: for all forces
	Force2DMapIter force_iter = force_map_.begin();
	for (; force_iter != force_map_.end() ; force_iter++)
	{
		// Delete the data
		if (force_iter->second != 0)
		{
			delete force_iter->second;
		}
	}

	// PARTICLE2DS: for all particles
	Particle2DListIter particle_iter = particle_list_.begin();
	for (; particle_iter != particle_list_.end() ; particle_iter++)
	{
		// Delete the data
		if (*particle_iter != 0)
		{
			delete *particle_iter;
		}
	}
}



/**
* Add particle to the system
*
* @param particle	Pointer to the new particle
*
* @return Return this particle's id
*
*/
Particle2DId Particle2DSystem::addParticle2D(Particle2D* pParticle2D)
{
	pParticle2D->id_ = particle_id_++;
	particle_list_.push_back(pParticle2D);
	num_particles_++;

	return pParticle2D->id_;
}



/**
* Add force to the system
*
* @param force	Pointer to the new force
*
* @return Return this force's id
*
*/
void Particle2DSystem::addForce2D(const std::string& name, Force2D* pForce2D)
{
	pForce2D->id_ = force_id_++;
	force_map_[name] =  pForce2D;
}



/**
* Get force pointer
*
* @param name	Get pointer to this force
*
* @return Return this force pointer. Null if it does not exist
*
*/
Force2D* Particle2DSystem::getForce2D(const std::string& name) const
{
	Force2DMapConstIter iter = force_map_.find(name);

	if (iter != force_map_.end())
		return iter->second;

	return 0;
}



/**
* Get vector of positions
*
* @param vPositions	Get all the positions
*
*/
void Particle2DSystem::getPositions(std::vector<glm::vec2>& vPositions) const
{
	JU::uint32 size = particle_list_.size();
	vPositions.resize(size);
	JU::uint32 index = 0;

	for (Particle2DListConstIter iter = particle_list_.begin(); iter != particle_list_.end(); ++iter)
	{
		vPositions[index++] = (*iter)->position_;
	}
}



/**
* Get vector of colors
*
* @param vColors	Vector with color for each particle
*
*/
void Particle2DSystem::getColors(std::vector<glm::vec4>& vColors) const
{
	JU::uint32 size = particle_list_.size();
	vColors.resize(size);
	JU::uint32 index = 0;

	for (Particle2DListConstIter iter = particle_list_.begin(); iter != particle_list_.end(); ++iter)
	{
		vColors[index++] = (*iter)->color_;
	}
}



/**
* Check all particles to see if they have expired
*
* @param time	Elapsed time since the last update (in milliseconds)
*
*/
void Particle2DSystem::cleanupParticle2Ds(f32 time)
{
	// PARTICLE2DS: for all particles
	Particle2DListIter particle_iter = particle_list_.begin();
	for (; particle_iter != particle_list_.end() ; particle_iter++)
	{
		if (!(*particle_iter)->is_inmortal_)
		{
			// Update the life left
			(*particle_iter)->lifetime_ -= time;

			// Erase it: it's dead
			if ((*particle_iter)->lifetime_ <= 0.0f)
			{
				Force2DMapIter force_iter = force_map_.begin();
				for (; force_iter != force_map_.end(); force_iter++)
				{
					force_iter->second->removeParticle2D((*particle_iter));
				}

				// Delete the particle's data
				if (*particle_iter != 0)
				{
					delete *particle_iter;
				}

				// Remove the pointer to the particle from the list
				particle_list_.erase(particle_iter);

				num_particles_--;

				return;
			}
		}
	}
}



/**
* Check all particles to see if they have expired
*
* @param time	Elapsed time since the last update (in milliseconds)
*
*/
void Particle2DSystem::cleanupForce2Ds(f32 time)
{
	// FORCE2DS: for all forces
	Force2DMapIter force_iter = force_map_.begin();
	for (; force_iter != force_map_.end(); force_iter++)
	{
		bool delete_force = false;

		switch ((force_iter->second)->type_)
		{
			case Force2D::TRANSIENT_ON_TIME:
				{
					// Update the life left
					(force_iter->second)->lifetime_ -= time;

					if ((force_iter->second)->lifetime_ <= 0.0f)
					{
						delete_force = true;
					}
				}
				break;

			case Force2D::TRANSIENT_ON_PARTICLE2DS:
				{
					if ((force_iter->second)->particle_set_.size() == 0)
					{
						delete_force = true;
					}
				}
				break;

			default:
				break;
		}

		if (delete_force)
		{
			// Delete the data
			if (force_iter->second != 0)
			{
				delete force_iter->second;
			}
			// Remove the pointer from the list
			force_map_.erase(force_iter);
		}
	}
}



/**
* Accumulate the forces on the particles they affect
*
* @param time	Elapsed time since the last update (in milliseconds)
*
* \note do we need to check whether the iterator is pointing to NULL
*/
void Particle2DSystem::accumulateForce2Ds(f32 time)
{
	// Reset all particle force accumulators
	// PARTICLE2DS: for all particles
	Particle2DListIter particle_iter = particle_list_.begin();
	for (; particle_iter != particle_list_.end() ; particle_iter++)
	{
		(*particle_iter)->force_acc_ = glm::vec2(0.0f);
	}

	// FORCE2DS: for all forces
	glm::mat3 model;
	moveable_.getToParentTransformation(model);

	Force2DMapConstIter force_iter = force_map_.begin();
	for (; force_iter != force_map_.end(); force_iter++)
	{
		force_iter->second->apply(model, time);
	}
}



/**
* Numerically integrate to compute the next state for each particle
*
* @param time	Elapsed time since the last update (in milliseconds)
*
*/
void Particle2DSystem::integrate(f32 time)
{
	// DEBUG start
	/*
	JU::Particle2DListConstIter iter = particle_list_.begin();
	glm::vec2 vel = (*iter)->velocity_;
	glm::vec2 acc = (*iter)->force_acc_ / (*iter)->mass_;
	std::printf ("Time     	   = %f\n", time);
	std::printf ("Velocity     = (%f, %f, %f)\n", vel.x, vel.y, vel.z);
	std::printf ("Acceleration = (%f, %f, %f)\n", acc.x, acc.y, acc.z);
	*/
	// DEBUG end

	for(Particle2DListIter iter = particle_list_.begin(); iter != particle_list_.end(); ++iter)
	{
		if ((*iter)->update_)
		{
			(*iter)->position_ += time * (*iter)->velocity_ * 0.001f;
			(*iter)->velocity_ += time * (*iter)->force_acc_ / (*iter)->mass_  * 0.001f;
		}
	}
}



/**
* Update all particles
*
* @param time	Elapsed time since the last update (in milliseconds)
*
* \note do we need to check whether the iterator is pointing to NULL
*/
void Particle2DSystem::update(f32 time)
{
	// Delete expired particles
	cleanupParticle2Ds(time);
	// Delete expired forces
	cleanupForce2Ds(time);
	// Accumulate forces for all the particles involved
	accumulateForce2Ds(time);
	// Update the state via numerical integration
	integrate(time);

}



/**
* Overloaded output operator
*
* @param out output ostream
* @param particle_system particle system to output
*
* @return output stream
*/
std::ostream& operator<<(std::ostream& out, const Particle2DSystem& particle_system)
{
	out << "Force2Ds: " << particle_system.force_map_.size() << std::endl;
	out << "---------------------------------------------" << std::endl;

	Force2DMapConstIter force_iter = particle_system.force_map_.begin();
	for( ; force_iter != particle_system.force_map_.end(); force_iter++)
		out << *(force_iter->second) << std::endl;

	out << "Particle2Ds: " << particle_system.num_particles_<< "(" << particle_system.particle_list_.size() << ")" << std::endl;
	out << "---------------------------------------------" << std::endl;

	Particle2DListConstIter particle_iter = particle_system.particle_list_.begin();
	for( ; particle_iter != particle_system.particle_list_.end(); particle_iter++)
		out << *(*particle_iter) << std::endl;

	return out;
}




} /* namespace JU */
