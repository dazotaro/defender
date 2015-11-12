/*
 * SpaceShip.cpp
 *
 *  Created on: Oct 21, 2015
 *      Author: jusabiaga
 */

#include "SpaceShip.hpp"
#include "../graphics/GLMesh2DInstance.hpp"	// GLMesh2DInstance
#include "../graphics/GLMesh2D.hpp"         // GLMesh2D
#include "../graphics/Texture.hpp"          // Texture
#include "../graphics/TextureManager.hpp"   // TextureManager
#include "../core/Keyboard.hpp"			    // Keyboard
#include "../core/Singleton.hpp"		    // Singleton
#include "../core/Moveable2D.hpp"		    // Moveable2D
#include "SquareMesh.hpp"		            // SquareMesh
#include "../core/Singleton.hpp"		    // Singleton
#include "../core/ResourceManager.hpp"	    // ResourceManager
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
SpaceShip::SpaceShip(const char* name, const char* texture_filename, bool is_collideable, f32 distance, f32 angle_delta)
            : SpriteObject(name, texture_filename, is_collideable), distance_(distance), angle_delta_(angle_delta)
{
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


} /* namespace JU */
