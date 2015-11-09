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
SpaceShip::SpaceShip(f32 posx, f32 posy, f32 angle, f32 distance, f32 angle_delta)
            : distance_(distance), angle_delta_(angle_delta)
{
    const std::string resource_name(SquareMesh::getId());

    GameObject::setMoveable2D(Moveable2D(posx, posy, angle, 1.0f, 1.0f));

    // GLMesh2D
    // -------------
    ResourceManager<const GLMesh2D>* prm_glmesh = Singleton<ResourceManager<const GLMesh2D>>::getInstance();

    const SquareMesh mesh;
    Shareable<const GLMesh2D>* pshare_mesh;
    if (!(pshare_mesh = prm_glmesh->referenceResource(resource_name)))
    {
        GLMesh2D* pglmesh = new GLMesh2D();
        pglmesh->init(mesh);
        pshare_mesh = prm_glmesh->addResource(resource_name, pglmesh);
    }

    // Texture
    // ----------------
    const char* filename("./data/textures/goodFighter.png");
    ResourceManager<const Texture>* prm_texture = Singleton<ResourceManager<const Texture>>::getInstance();
    Shareable<const Texture>* pshare_texture;
    if (!(pshare_texture = prm_texture->referenceResource(filename)))
    {
        Texture* ptexture = new Texture(filename);
        pshare_texture = prm_texture->addResource(filename, ptexture);
    }

    // GLMesh2DInstance
    // ----------------
    GameObject::pmesh_instance_ = new GLMesh2DInstance(pshare_mesh, pshare_texture);

    // RigidBody
    // -------------
    ResourceManager<BoundingCircle>* pshare_boundingbox = Singleton<ResourceManager<BoundingCircle>>::getInstance();

    Shareable<BoundingCircle>* pboundingcircle_resource;
    if (!(pboundingcircle_resource = pshare_boundingbox->referenceResource(resource_name)))
    {
       BoundingCircle* pbounding_circle = new BoundingCircle(glm::vec2(0.0f, 0.0f), 0.5f);
       pboundingcircle_resource = pshare_boundingbox->addResource(resource_name, pbounding_circle);
    }

    GameObject::setRigitBody(new RigidBody(pboundingcircle_resource));
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
void SpaceShip::render(const GLSLProgram &program, const glm::mat3 & model,
        const glm::mat3 &view) const
{
    glm::mat3 toparent;
    moveable_.getToParentTransformation(toparent);

    glm::mat3 new_model = model * toparent;

    pmesh_instance_->render(program, new_model, view);
}

} /* namespace JU */
