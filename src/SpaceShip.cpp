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
SpaceShip::SpaceShip(f32 posx, f32 posy, f32 angle, f32 distance, f32 angle_delta) : distance_(distance), angle_delta_(angle_delta)
{
    // GLMesh2D
    // -------------
    JU::GLMesh2D* p_glmesh = new JU::GLMesh2D();
    p_glmesh->init();

    // GLMesh2DInstance
    // -------------
    GameObject::setMeshInstance(new JU::GLMesh2DInstance(p_glmesh));
    GameObject::setMoveable2D(new JU::Moveable2D(posx, posy, angle, 1.0f, 1.0f));
}


/**
* @brief Destructor
*
*/
SpaceShip::~SpaceShip()
{
	delete mesh_instance_->getGLMesh();
	delete mesh_instance_;
	delete moveable_;
}


/**
* @brief Update function
*
* @param milliseconds  Time elapsed since the last call (in milliseconds)
*
*/
void SpaceShip::update(JU::f32 milliseconds)
{
	Keyboard* keyboard = Singleton<Keyboard>::getInstance();

	if (keyboard->isKeyDown(SDL_SCANCODE_LEFT))
	{
		moveable_->moveX(-distance_ * milliseconds);
	}
	else if (keyboard->isKeyDown(SDL_SCANCODE_RIGHT))
	{
		moveable_->moveX(distance_ * milliseconds);
	}

	if (keyboard->isKeyDown(SDL_SCANCODE_UP))
	{
		moveable_->moveY(distance_ * milliseconds);
	}
	else if (keyboard->isKeyDown(SDL_SCANCODE_DOWN))
	{
		moveable_->moveY(-distance_ * milliseconds);
	}

	if (keyboard->isKeyDown(SDL_SCANCODE_A))
	{
		moveable_->rotate(angle_delta_ * milliseconds);
	}
	else if (keyboard->isKeyDown(SDL_SCANCODE_S))
	{
		moveable_->rotate(-angle_delta_ * milliseconds);
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
	moveable_->getToParentTransformation(toparent);

	glm::mat3 new_model = model * toparent;

	mesh_instance_->render(program, new_model, view);
}


} /* namespace JU */
