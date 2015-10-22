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

SpaceShip::SpaceShip(f32 pos_x, f32 pos_y, f32 angle)
{
    // GLMesh2D
    // -------------
    JU::GLMesh2D* p_glmesh = new JU::GLMesh2D();
    p_glmesh->init();

    // GLMesh2DInstance
    // -------------
    GameObject::setMeshInstance(new JU::GLMesh2DInstance(p_glmesh));
    GameObject::setMoveable2D(new JU::Moveable2D(pos_x, pos_y, angle, 1.0f, 1.0f));
}


SpaceShip::~SpaceShip()
{
	delete mesh_instance_->getGLMesh();
	delete mesh_instance_;
	delete moveable_;
}


void SpaceShip::update(JU::f32 milliseconds)
{
	Keyboard* keyboard = Singleton<Keyboard>::getInstance();

	if (keyboard->isKeyDown(SDL_SCANCODE_LEFT))
	{
		moveable_->position_[0] -= 0.001f * moveable_->scale_[0];
	}
	else if (keyboard->isKeyDown(SDL_SCANCODE_RIGHT))
	{
		moveable_->position_[0] += 0.001f * moveable_->scale_[0];
	}

	if (keyboard->isKeyDown(SDL_SCANCODE_A))
	{
		moveable_->angle_ += 0.001f;
	}
	else if (keyboard->isKeyDown(SDL_SCANCODE_S))
	{
		moveable_->angle_ -= 0.001f;
	}
}


void SpaceShip::render(const GLSLProgram &program, const glm::mat3 & model, const glm::mat3 &view) const
{
	glm::mat3 toparent;
	moveable_->getToParentTransformation(toparent);

	glm::mat3 new_model = model * toparent;

	mesh_instance_->render(program, new_model, view);
}


} /* namespace JU */
