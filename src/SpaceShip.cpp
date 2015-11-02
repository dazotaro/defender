/*
 * SpaceShip.cpp
 *
 *  Created on: Oct 21, 2015
 *      Author: jusabiaga
 */

#include "SpaceShip.hpp"
#include "../graphics/GLMesh2DInstance.hpp"	// GLMesh2DInstance
#include "../graphics/GLMesh2D.hpp"			// GLMesh2D
#include "../core/Keyboard.hpp"			// Keyboard
#include "../core/Singleton.hpp"		// Singleton
#include "../core/Moveable2D.hpp"		// Moveable2D
#include "TriangleMesh.hpp"		// TriangleMesh
#include "../core/Singleton.hpp"		// Singleton
#include "../core/ResourceManager.hpp"	// ResourceManager
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
	const std::string resource_name ("/proc/triangle");

    // GLMesh2D
    // -------------
	ResourceManager<GLMesh2D>* prm_glmesh = Singleton<ResourceManager<GLMesh2D>>::getInstance();

	const TriangleMesh mesh;
    GLMesh2D* pglmesh;
    if (!(pglmesh = prm_glmesh->referenceResource(resource_name)))
    {
    	pglmesh = new GLMesh2D();
    	pglmesh->init(mesh);
    	prm_glmesh->addResource(resource_name, pglmesh);
    }

    // GLMesh2DInstance
    // -------------
	ResourceManager<GLMesh2DInstance>* prm_glmeshinstance = Singleton<ResourceManager<GLMesh2DInstance>>::getInstance();

    GLMesh2DInstance* pglmeshinstance;
    if (!(pglmeshinstance = prm_glmeshinstance->referenceResource(resource_name)))
    {
    	pglmeshinstance = new GLMesh2DInstance(pglmesh);
    	prm_glmeshinstance->addResource(resource_name, pglmeshinstance);
    }

    GameObject::setMeshInstance(pglmeshinstance);
    GameObject::setMoveable2D(Moveable2D(posx, posy, angle, 1.0f, 1.0f));

    // RigidBody
    // -------------
	ResourceManager<BoundingCircle>* prm_boundingcircle = Singleton<ResourceManager<BoundingCircle>>::getInstance();

	BoundingCircle* pbounding_circle;
    if (!(pbounding_circle = prm_boundingcircle->referenceResource(resource_name)))
    {
    	pbounding_circle = new BoundingCircle(glm::vec2(0.0f, 0.0f), 0.5f);
    	prm_boundingcircle->addResource(resource_name, pbounding_circle);
    }

    prigid_body_ = new RigidBody(pbounding_circle);

    GameObject::setRigitBody(prigid_body_);
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
		moveable_.moveY(distance_ * milliseconds);
	}
	else if (keyboard->isKeyDown(SDL_SCANCODE_DOWN))
	{
		moveable_.moveY(-distance_ * milliseconds);
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
