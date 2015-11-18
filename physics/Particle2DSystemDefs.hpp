/*
 * Particle2DSystemDefs.hpp
 *
 *  Created on: Jan 25, 2014
 *      Author: aitatxo
 */

#ifndef PARTICLE2DSYSTEMDEFS_HPP_
#define PARTICLE2DSYSTEMDEFS_HPP_

// Global includes
#include <list>		// std::list
#include <map>		// std::map
#include <set>		// std::unordered_set
#include <vector>	// std::vector
#include <string>	// std::string
#include <glm/glm.hpp>			// glm::vec3

namespace JU
{
	// Forward Declarations
	class Particle2D;
	class Force2D;

	// Typedefs
	typedef uint32 Particle2DId;
	typedef uint32 Force2DId;

	typedef std::list<Particle2D*> 			Particle2DList;
	typedef Particle2DList::const_iterator 	Particle2DListConstIter;
	typedef Particle2DList::iterator 			Particle2DListIter;

	typedef std::map<Particle2DId, Particle2D*> Particle2DMap;
	typedef Particle2DMap::const_iterator 	Particle2DMapConstIter;
	typedef Particle2DMap::iterator 			Particle2DMapIter;

	typedef std::set<Particle2D*> 			Particle2DSet;
	typedef Particle2DSet::const_iterator 	Particle2DSetConstIter;
	typedef Particle2DSet::iterator 			Particle2DSetIter;

	typedef std::list<Force2D*> 				Force2DList;
	typedef Force2DList::const_iterator 		Force2DListConstIter;
	typedef Force2DList::iterator 			Force2DListIter;

	typedef std::map<std::string, Force2D*> 	Force2DMap;
	typedef Force2DMap::const_iterator 		Force2DMapConstIter;
	typedef Force2DMap::iterator 				Force2DMapIter;

	typedef std::set<Force2D*> 				Force2DSet;
	typedef Force2DSet::iterator 				Force2DSetIter;

	typedef std::vector<Force2DId>			Force2DIdVector;
	typedef Force2DIdVector::const_iterator	Force2DIdVectorConstIter;
	typedef Force2DIdVector::iterator			Force2DIdVectorIter;

	struct Plane
	{
		Plane() {}
		Plane(const glm::vec3& point, const glm::vec3 normal) : point_(point), normal_(normal) {}

		glm::vec3 point_;
		glm::vec3 normal_;
	};
	typedef std::map<std::string, Plane> 	PlaneMap;
	typedef PlaneMap::const_iterator 		PlaneMapConstIter;
	typedef PlaneMap::iterator 				PlaneMapIter;

} /* namespace JU */


#endif /* PARTICLE2DSYSTEMDEFS_HPP_ */
