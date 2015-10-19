/*
 * GLMesh2DInstance.hpp
 *
 *  Created on: Oct 19, 2015
 *      Author: jusabiaga
 */

#ifndef GLMESH2DINSTANCE_HPP_
#define GLMESH2DINSTANCE_HPP_

#include "Renderable2DInterface.hpp"	// Renderable2DInterface

namespace JU
{

// Forward Declarations
class GLMesh2D;

class GLMesh2DInstance : public Renderable2DInterface
{
	public:
		GLMesh2DInstance(GLMesh2D* gl_mesh);
		virtual ~GLMesh2DInstance();

	public:
		// Renderable2DInterface
        void render(const GLSLProgram &program,	const glm::mat3 & model, const glm::mat3 &view) const;

	private:
        GLMesh2D* gl_mesh_;

};

} /* namespace JU */

#endif /* GLMESH2DINSTANCE_HPP_ */
