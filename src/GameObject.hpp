/*
 * GameObject.hpp
 *
 *  Created on: Oct 21, 2015
 *      Author: jusabiaga
 */

#ifndef GAMEOBJECT_HPP_
#define GAMEOBJECT_HPP_

#include "Defs.hpp"			// JU::f32
#include "Moveable2D.hpp"	// Moveable2D
#include <glm/glm.hpp>		// mat3

namespace JU
{

// Forward Declarations
class GLMesh2DInstance;
class GLSLProgram;

class GameObject
{
	public:
		GameObject();
		GameObject(GLMesh2DInstance* mesh_instance, Moveable2D moveable);
		virtual ~GameObject();

		const GLMesh2DInstance* getMeshInstance() const;
		void setMeshInstance(GLMesh2DInstance* mesh_instance);
		void setMoveable2D(Moveable2D moveable);

		virtual void update(JU::f32 milliseconds) = 0;
		virtual void render(const GLSLProgram &program, const glm::mat3 & model, const glm::mat3 &view) const;

	protected:
		GLMesh2DInstance* mesh_instance_;	//!< Renderable component
		Moveable2D		  moveable_;		//!< Position and orientation
};

} /* namespace JU */

#endif /* GAMEOBJECT_HPP_ */
