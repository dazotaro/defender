/*
 * Particle2DSystem.hpp
 *
 *  Created on: Jan 24, 2014
 *      Author: dazotaro
 */

#ifndef PARTICLE2DSYSTEM_HPP_
#define PARTICLE2DSYSTEM_HPP_

// Local includes
#include "Particle2DSystemDefs.hpp"		// Particle2DList, Force2DList
#include "../core/Defs.hpp"             // custom types
#include "../core/Moveable2D.hpp"       // Moveable2D
// Global includes
#include <glm/glm.hpp>			// glm::vec3


namespace JU
{

// Forward declarations
class Particle2D;
class Force2D;

class Particle2DSystem
{
	public:

		Particle2DSystem(const Moveable2D &moveable);
		virtual ~Particle2DSystem();

		Particle2DId addParticle2D(Particle2D* pParticle2D);

		void addForce2D(const std::string& name, Force2D* pForce2D);
		Force2D* getForce2D(const std::string& name) const;

		void getPositions(std::vector<glm::vec2>& vPositions) const;
		void getColors(std::vector<glm::vec4>& vColors) const;

		void update(f32 time);

	private:

		void cleanupParticle2Ds(f32 time);
		void cleanupForce2Ds(f32 time);

		void accumulateForce2Ds(f32 time);
		void integrate(f32 time);

	public:

		// Friend functions
		friend std::ostream& operator<<(std::ostream& out, const Particle2DSystem& particle_system);

	private:

		Moveable2D      moveable_;

		// Particle2D Storage
		Particle2DList 	particle_list_;
		uint32	 		num_particles_;	// we want to guarantee O(1), independent of STL implementation
		Particle2DId 	particle_id_;

		// Force2D Storage
		Force2DMap 		force_map_;
		Force2DId 		force_id_;
};

} /* namespace JU */
#endif /* PARTICLE2DSYSTEM_HPP_ */
