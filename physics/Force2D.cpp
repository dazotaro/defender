/*
 * Force2D.cpp
 *
 *  Created on: Jan 25, 2014
 *      Author: dazotaro
 */

// Local Includes
#include "Force2D.hpp"	// JU::Force2D
#include "Particle2D.hpp"	// JU::Particle2D

// Global Includes
#include <sstream>		// std::ostringstream
#include <glm/gtx/norm.hpp>

namespace JU
{

Force2D::Force2D(TerminationType type, f32 lifetime) : id_(0), type_(type), lifetime_(lifetime)
{
}



Force2D::~Force2D()
{
}



void Force2D::addParticle2D(Particle2D* pParticle2D)
{
	particle_set_.insert(pParticle2D);
}



void Force2D::removeParticle2D(Particle2D* pParticle2D)
{
	particle_set_.erase(pParticle2D);
}



std::string Force2D::getInfoString() const
{
	std::ostringstream out;

	out << "Force2D id: " 	<< id_ 		<< std::endl;
	out << "\tAddress: " 	<< this		<< std::endl;

	switch (type_)
	{
		case Force2D::PERSISTENT:
			out << "\tType: " << type_	<< " (PERSISTENT)" << std::endl;
			break;

		case Force2D::TRANSIENT_ON_PARTICLE2DS:
			out << "\tType: " << type_	<< " (TRANSIENT_ON_PARTICLE2DS)" << std::endl;
			out << "\tLife: " << particle_set_.size()	<< " (particles)" << std::endl;

			break;

		case Force2D::TRANSIENT_ON_TIME:
			out << "\tType: " << type_	<< " (TRANSIENT_ON_TIME)" << std::endl;
			out << "\tLife: " << lifetime_ << " (milliseconds)" << std::endl;
			break;

		default:
			out << "UNKNOWN TYPE)";
			break;
	}


	out << "\tLinked particles: ";
	Particle2DSetConstIter particle_iter = particle_set_.begin();
	for (; particle_iter != particle_set_.end(); particle_iter++)
	{
		out << *particle_iter << ", ";
	}
	out << std::endl;

	return out.str();
}

/**
* Overloaded output operator
*
* @param out output ostream
* @param force output ostream
*
* @return output stream
*/
std::ostream& operator<<(std::ostream& out, const Force2D& force)
{
	out << force.getInfoString() << std::endl;

	return out;
}



GravityForce2D::GravityForce2D(f32 g) : Force2D(PERSISTENT), g_(g)
{
}



GravityForce2D::~GravityForce2D()
{
}



void GravityForce2D::apply(const glm::mat3& model, f32 time) const
{
	Particle2DSetIter particle_iter = particle_set_.begin();
	for (; particle_iter != particle_set_.end(); particle_iter++)
	{
		(*particle_iter)->force_acc_ += glm::vec2(0.0f, -g_) * (*particle_iter)->mass_;
	}
}



std::string GravityForce2D::getInfoString() const
{
	std::ostringstream out;

	out << "\tDescription: Gravity Force2D" << std::endl;
	out << "\tAcceleration: " << g_ << std::endl;

	return Force2D::getInfoString() + out.str();
}



DragForce2D::DragForce2D(f32 drag) : Force2D(TRANSIENT_ON_PARTICLE2DS), drag_(drag)
{
}



DragForce2D::~DragForce2D()
{
}



void DragForce2D::apply(const glm::mat3& model, f32 time) const
{
	Particle2DSetConstIter particle_iter = particle_set_.begin();
	for (; particle_iter != particle_set_.end(); particle_iter++)
	{
		(*particle_iter)->force_acc_ += -drag_ * (*particle_iter)->velocity_;
	}
}



std::string DragForce2D::getInfoString() const
{
	std::ostringstream out;

	out << "\tDescription: Drag Force2D" << std::endl;
	out << "\tDrag: " << drag_ << std::endl;

	return Force2D::getInfoString() + out.str();
}



ThrustForce2D::ThrustForce2D(const glm::vec2& force, f32 time) : Force2D(TRANSIENT_ON_TIME, time), force_(force)
{
}



ThrustForce2D::~ThrustForce2D()
{
}



void ThrustForce2D::apply(const glm::mat3& model, f32 time) const
{
	Particle2DSetConstIter particle_iter = particle_set_.begin();
	for (; particle_iter != particle_set_.end(); particle_iter++)
	{
		(*particle_iter)->force_acc_ += force_;
	}
}



std::string ThrustForce2D::getInfoString() const
{
	std::ostringstream out;

	out << "\tDescription: Thrust Force2D" << std::endl;
	out << "\tThrust Force2D: (" 	<< force_.x << ", "
                                    << force_.y << ")" << std::endl;

	return Force2D::getInfoString() + out.str();
}



SpringForce2D::SpringForce2D(f32 ks, f32 equilibrium_distance)
				: Force2D(TRANSIENT_ON_PARTICLE2DS), ks_(ks), equilibrium_distance_(equilibrium_distance)
{
}



SpringForce2D::~SpringForce2D()
{
}



void SpringForce2D::apply(const glm::mat3& model, f32 time) const
{
	if (particle_set_.size() != 2)
		std::printf("Spring forces with more than two particles not yet supported\n");

	Particle2DSetConstIter iter = particle_set_.begin();
	Particle2DSetConstIter particle1 = iter++;
	Particle2DSetConstIter particle2 = iter;

	glm::vec2 P1toP2 ((*particle2)->position_ - (*particle1)->position_);
	JU::f32 P1toP2distance = glm::length(P1toP2);

	glm::vec2 P1toP2normalized = glm::normalize(P1toP2);

	glm::vec2 force (-ks_ * (P1toP2distance - equilibrium_distance_) * P1toP2normalized);

	(*particle1)->force_acc_ -= force;
	(*particle2)->force_acc_ += force;
}



std::string SpringForce2D::getInfoString() const
{
	std::ostringstream out;

	out << "\tDescription: Spring Force2D" << std::endl;
	out << "\tStiffness coefficient: " << ks_ << std::endl;
	out << "\tEquilibrium distance: " << equilibrium_distance_ << std::endl;

	return Force2D::getInfoString() + out.str();
}



DampedSpringForce2D::DampedSpringForce2D(f32 ks, f32 kd, f32 equilibrium_distance)
				: Force2D(TRANSIENT_ON_PARTICLE2DS), ks_(ks), kd_(kd), equilibrium_distance_(equilibrium_distance)
{
}



DampedSpringForce2D::~DampedSpringForce2D()
{
}



void DampedSpringForce2D::apply(const glm::mat3& model, f32 time) const
{
	if (particle_set_.size() != 2)
		std::printf("Spring forces with more than two particles not yet supported\n");

	Particle2DSetConstIter iter = particle_set_.begin();
	Particle2DSetConstIter particle1 = iter++;
	Particle2DSetConstIter particle2 = iter;

	glm::vec2 P1toP2 ((*particle2)->position_ - (*particle1)->position_);
	JU::f32 P1toP2distance = glm::length(P1toP2);
	glm::vec2 P1toP2normalized = glm::normalize(P1toP2);

	glm::vec2 V1toV2 ((*particle2)->velocity_ - (*particle1)->velocity_);

	glm::vec2 force ((-ks_ * (P1toP2distance - equilibrium_distance_) - kd_ * V1toV2 * P1toP2normalized) * P1toP2normalized);

	(*particle1)->force_acc_ -= force;
	(*particle2)->force_acc_ += force;
}



std::string DampedSpringForce2D::getInfoString() const
{
	std::ostringstream out;

	out << "\tDescription: Damped Spring Force2D" << std::endl;
	out << "\tStiffness coefficient: " << ks_ << std::endl;
	out << "\tEquilibrium distance: " << equilibrium_distance_ << std::endl;

	return Force2D::getInfoString() + out.str();
}



} /* namespace JU */
