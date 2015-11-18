/*
 * Force2D.hpp
 *
 *  Created on: Jan 25, 2014
 *      Author: dazotaro
 */

#ifndef FORCE2D_HPP_
#define FORCE2D_HPP_

// Local includes
#include <JU/core/Defs.hpp>				// custom types
#include "Particle2DSystemDefs.hpp"		// Particle2DList, Force2DList

// Global includes
#include <iostream>				// std:;ostream, std::endl
#include <glm/glm.hpp>      			// glm::vec2

namespace JU
{

/*! Force2D base class */
class Force2D
{

	public:

		/** Types of forces (based on the way they are eliminated).
		 */
		enum TerminationType
		{
			PERSISTENT,				/**< it has to be explicitly deleted */
			TRANSIENT_ON_PARTICLE2DS,	/**< it is deleted when all the particles it is linked to die */
			TRANSIENT_ON_TIME,		/**< it is deleted when it reaches a maximum lifetime */
		};

		Force2D(TerminationType type = PERSISTENT, f32 lifetime = 0.0f);
		virtual ~Force2D();

		virtual void addParticle2D(Particle2D* pParticle2D);
		virtual void apply(const glm::mat3& model, f32 time) const = 0;

		void removeParticle2D(Particle2D* pParticle2D);

		virtual std::string getInfoString() const;

		friend std::ostream& operator<<(std::ostream& out, const Force2D& force);

	public:

		Force2DId 		id_;
		TerminationType type_;				/**< Is force transient or eternal */
		f32 			lifetime_;			/**< Life left of the force (in milliseconds)*/

		Particle2DSet 	particle_set_;		/**< Particle2Ds subject to this force */
};



class GravityForce2D : public Force2D
{
	public:
		GravityForce2D(f32 g = 9.80665);
		virtual ~GravityForce2D();

		void apply(const glm::mat3& model, f32 time) const;

		std::string getInfoString() const;

	private:

		f32 g_;		/**< Acceleration due to gravity at earth's surface */
};



class DragForce2D: public Force2D
{
	public:
		DragForce2D(f32 drag = 9.80665);
		virtual ~DragForce2D();

		void apply(const glm::mat3& model, f32 time) const;

		std::string getInfoString() const;

	private:

		f32 drag_;		/**< Acceleration due to gravity at earth's surface */
};



class ThrustForce2D : public Force2D
{
	public:
		ThrustForce2D(const glm::vec2& force, f32 time);
		virtual ~ThrustForce2D();

		void apply(const glm::mat3& model, f32 time) const;

		std::string getInfoString() const;

	private:

		glm::vec2 force_;		/**< Thrust force */
};



class SpringForce2D : public Force2D
{
	public:
		SpringForce2D(f32 ks, f32 equilibrium_distance);
		virtual ~SpringForce2D();

		void apply(const glm::mat3& model, f32 time) const;

		std::string getInfoString() const;

	private:

		f32 ks_;					/**< Stiffness of the spring to be applied in Hooke's Law */
		f32 equilibrium_distance_;	/**< Distance of equilibrium */
};



class DampedSpringForce2D : public Force2D
{
	public:
		DampedSpringForce2D(f32 ks, f32 kd, f32 equilibrium_distance);
		virtual ~DampedSpringForce2D();

		void apply(const glm::mat3& model, f32 time) const;

		std::string getInfoString() const;

	private:

		f32 ks_;					/**< Stiffness of the spring to be applied in Hooke's Law */
		f32 kd_;					/**< Damping coefficient */
		f32 equilibrium_distance_;	/**< Distance of equilibrium */
};



} /* namespace JU */
#endif /* FORCE2D_HPP_ */
