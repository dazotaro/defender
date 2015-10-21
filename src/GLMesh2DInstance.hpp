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
		GLMesh2DInstance(const GLMesh2D* gl_mesh, const glm::vec2& scale);
		virtual ~GLMesh2DInstance();

	public:
		const GLMesh2D* getGLMesh() const { return gl_mesh_; }
		// Renderable2DInterface
        void render(const GLSLProgram &program,	const glm::mat3 & model, const glm::mat3 &view) const;

	private:
        const GLMesh2D* gl_mesh_;
        glm::vec2 		scale_;

};

} /* namespace JU */

#endif /* GLMESH2DINSTANCE_HPP_ */
