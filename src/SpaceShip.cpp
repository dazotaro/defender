/*
 * SpaceShip.cpp
 *
 *  Created on: Oct 21, 2015
 *      Author: jusabiaga
 */

#include "SpaceShip.hpp"
#include "GLMesh2DInstance.hpp"	// GLMesh2DInstance
#include "GLMesh2D.hpp"			// GLMesh2D
#include "Keyboard.hpp"			// Keyboard
#include "Singleton.hpp"		// Singleton
#include "Moveable2D.hpp"		// Moveable2D
#include "SquareMesh.hpp"		// SquareMesh
#include "Singleton.hpp"		// Singleton
#include "ResourceManager.hpp"	// ResourceManager
#include "../physics/RigidBody.hpp"

namespace JU
{

/**
* @brief Non-default constructor
*
* @param posx  X coordinate of position
* @param posy  Y coordinate of position
* @param angle Angle of orientation in radians
*
*/
SpaceShip::SpaceShip(f32 posx, f32 posy, f32 angle, f32 distance, f32 angle_delta)
			: distance_(distance), angle_delta_(angle_delta)
{
    // GLMesh2D
    // -------------
	ResourceManager<GLMesh2D>* prm_glmesh = Singleton<ResourceManager<GLMesh2D>>::getInstance();

	const SquareMesh mesh;
    GLMesh2D* pglmesh;
    if (!(pglmesh = prm_glmesh->referenceResource("/proc/glmesh/square")))
    {
    	pglmesh = new GLMesh2D();
    	pglmesh->init(mesh);
    	prm_glmesh->addResource("/proc/glmesh/square", pglmesh);
    }

    // GLMesh2DInstance
    // -------------
	ResourceManager<GLMesh2DInstance>* prm_glmeshinstance = Singleton<ResourceManager<GLMesh2DInstance>>::getInstance();

    GLMesh2DInstance* pglmeshinstance;
    if (!(pglmeshinstance = prm_glmeshinstance->referenceResource("/proc/glmeshinstance/square")))
    {
    	pglmeshinstance = new GLMesh2DInstance(pglmesh);
    	prm_glmeshinstance->addResource("/proc/glmeshinstance/square", pglmeshinstance);
    }

    GameObject::setMeshInstance(pglmeshinstance);
    GameObject::setMoveable2D(Moveable2D(posx, posy, angle, 1.0f, 1.0f));

    // RigidBody
    // -------------
	ResourceManager<RigidBody>* prm_rigidbody = Singleton<ResourceManager<RigidBody>>::getInstance();

	RigidBody* prigid_body;
    if (!(prigid_body = prm_rigidbody->referenceResource("/proc/rigidbody/square")))
    {
    	prigid_body = new RigidBody(BoundingCircle(glm::vec2(0.0f, 0.0f), 0.5f));
    	prm_rigidbody->addResource("/proc/rigidbody/square", prigid_body);
    }

    GameObject::setRigitBody(prigid_body);
}


/**
* @brief Destructor
*
*/
SpaceShip::~SpaceShip()
{
}


/**
* @brief Update function
*
* @param milliseconds  Time elapsed since the last call (in milliseconds)
*
*/
void SpaceShip::update(f32 milliseconds)
{
	Keyboard* keyboard = Singleton<Keyboard>::getInstance();

	if (keyboard->isKeyDown(SDL_SCANCODE_LEFT))
	{
		moveable_.rotate(angle_delta_ * milliseconds);
	}
	else if (keyboard->isKeyDown(SDL_SCANCODE_RIGHT))
	{
		moveable_.rotate(-angle_delta_ * milliseconds);
	}

	if (keyboard->isKeyDown(SDL_SCANCODE_UP))
	{
		moveable_.moveX(distance_ * milliseconds);
	}
	else if (keyboard->isKeyDown(SDL_SCANCODE_DOWN))
	{
		moveable_.moveX(-distance_ * milliseconds);
	}
}


/**
* @brief Render function
*
* @detail GameObject-inherited render function
*
* @param program GLSL program handle (to set uniforms)
* @param model   Model matrix to parent's coordinate system
* @param view    Camera's view matrix (world to NDC)
*
*/
void SpaceShip::render(const GLSLProgram &program, const glm::mat3 & model, const glm::mat3 &view) const
{
	glm::mat3 toparent;
	moveable_.getToParentTransformation(toparent);

	glm::mat3 new_model = model * toparent;

	mesh_instance_->render(program, new_model, view);
}


} /* namespace JU */
