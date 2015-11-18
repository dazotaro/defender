/*
 * Particle2D.cpp
 *
 *  Created on: Jan 24, 2014
 *      Author: dazotaro
 */

// Local includes
#include "Particle2D.hpp"

// Global includes
#include <iostream>		// std::cout, std::endl



namespace JU
{

/**
* Constructor
*
* @param position	Initial position
* @param velocity	Initial velocity
* @param mass		Mass of the particle
* @param lifetime	Life (in seconds) of this particle
*/
Particle2D::Particle2D(f32 mass,
				   const glm::vec2& position,
				   const glm::vec2& velocity,
				   const glm::vec4& color,
				   bool update,
				   bool is_inmortal,
				   JU::f32 lifetime)
			: id_(0),
			  mass_ (mass),
			  position_(position),
			  velocity_(velocity),
			  force_acc_(glm::vec2(0.0f)),
			  color_(color),
			  update_(update),
			  is_inmortal_(is_inmortal),
			  lifetime_(lifetime)
{
}



/**
* Destructor
*/
Particle2D::~Particle2D()
{
	// TODO Auto-generated destructor stub
}



/**
* Reset force accumulator
*
*/
inline void Particle2D::resetForce2DAcc()
{
	force_acc_.x = 0.0f;
	force_acc_.y = 0.0f;
}



/**
* Overloaded output operator
*
* @param out output ostream
* @param particle output ostream
*
* @return output stream
*/
std::ostream& operator<<(std::ostream& out, const Particle2D& particle)
{

	out << "Particle2D id: " 	<< particle.id_ << std::endl;
	out << "\tAddress: " 	<< &particle << std::endl;
	out << "\tUpdate: " 	<< particle.update_ << std::endl;
	out << "\tMass: " 		<< particle.mass_ << std::endl;
	out << "\tLife: " 		<< particle.lifetime_ << std::endl;
	out << "\tPosition: (" 	<< particle.position_.x << ", "
                            << particle.position_.y << ")" << std::endl;
	out << "\tVelocity: (" 	<< particle.velocity_.x << ", "
                            << particle.velocity_.y << ")" << std::endl;
	out << "\tForce2D:  (" 	<< particle.force_acc_.x << ", "
                            << particle.force_acc_.y << ")" << std::endl;
	out << "\tColor:    (" 	<< particle.color_.r << ", "
							<< particle.color_.g << ", "
							<< particle.color_.b << ", "
							<< particle.color_.a << ")" << std::endl;

	return out;
}



} /* namespace JU */
