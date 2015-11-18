/*
 * Particle2D.hpp
 *
 *  Created on: Jan 24, 2014
 *      Author: dazotaro
 */

#ifndef PARTICLE2D_HPP_
#define PARTICLE2D_HPP_

// Local includes
#include <JU/core/Defs.hpp>			// Custom basic types
#include "Particle2DSystemDefs.hpp"	// Particle2DId

// Global includes
#include <glm/glm.hpp>          	// glm::vec2

namespace JU
{

// Forward Declarations
//class Force2D;

/*! \class Particle2D
    \brief Base class for all particle types

    It provides all basic information required of a particle
*/
class Particle2D
{
	public:

		Particle2D(f32 mass,
				 const glm::vec2& position,
				 const glm::vec2& velocity,
				 const glm::vec4& color,
				 bool update = true,
				 bool is_inmortal = true,
				 JU::f32 lifetime = 0.0f);
		virtual ~Particle2D();

		void resetForce2DAcc();

		// Friend functions
		friend std::ostream& operator<<(std::ostream& out, const Particle2D& particle);

	public:

		Particle2DId id_;					/**< particle id (for debugging purposes */

		f32 	  mass_;
		glm::vec2 position_;
		glm::vec2 velocity_;
		glm::vec2 force_acc_;		/**< Force2D accumulator */
		glm::vec4 color_;
		bool update_;				/**< Exclude this particle from the integrator? */

		bool is_inmortal_;
		f32 lifetime_;					/**< Life left of the force (in milliseconds) */
};

} /* namespace JU */
#endif /* PARTICLE2D_HPP_ */
