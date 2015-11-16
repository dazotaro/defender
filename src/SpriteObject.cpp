/*
 * SpriteObject.cpp
 *
 *  Created on: Nov 12, 2015
 *      Author: jusabiaga
 */

#include "SpriteObject.hpp"
#include "../graphics/GLMesh2DInstance.hpp" // GLMesh2DInstance
#include "../graphics/GLMesh2D.hpp"         // GLMesh2D
#include "../core/Keyboard.hpp"         // Keyboard
#include "../core/Singleton.hpp"        // Singleton
#include "../core/Moveable2D.hpp"       // Moveable2D
#include "SquareMesh.hpp"               // SquareMesh
#include "../core/Singleton.hpp"        // Singleton
#include "../core/ResourceManager.hpp"  // ResourceManager
#include "../physics/RigidBody.hpp"         // RigidBody

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
SpriteObject::SpriteObject(const char* name, const char* texture_filename, bool is_collideable)
{
    GameObject::setName(std::string(name));

    const std::string resource_name(SquareMesh::getId());

    // GLMesh2D
    // -------------
    ResourceManager<const GLMesh2D>* prm_glmesh = Singleton<ResourceManager<const GLMesh2D>>::getInstance();

    const SquareMesh mesh;
    Shareable<const GLMesh2D>* pshare_mesh;
    if (!(pshare_mesh = prm_glmesh->referenceResource(resource_name)))
    {
        GLMesh2D* pglmesh = new GLMesh2D();
        pglmesh->transferDataGPU(mesh);
        pshare_mesh = prm_glmesh->addResource(resource_name, pglmesh);
    }

    // Texture
    // ----------------
    ResourceManager<const Texture>* prm_texture = Singleton<ResourceManager<const Texture>>::getInstance();
    Shareable<const Texture>* pshare_texture;
    if (!(pshare_texture = prm_texture->referenceResource(texture_filename)))
    {
        Texture* ptexture = new Texture(texture_filename);
        pshare_texture = prm_texture->addResource(texture_filename, ptexture);
    }

    // GLMesh2DInstance
    // ----------------
    GameObject::pmesh_instance_ = new GLMesh2DInstance(pshare_mesh, pshare_texture);

    if (is_collideable)
    {
        // RigidBody
        // -------------
        ResourceManager<BoundingCircle>* prm_boundingcircle = Singleton<ResourceManager<BoundingCircle>>::getInstance();

        Shareable<BoundingCircle>* pshare_boundingbox;
        if (!(pshare_boundingbox = prm_boundingcircle->referenceResource(resource_name)))
        {
           BoundingCircle* pbounding_circle = new BoundingCircle(glm::vec2(0.0f, 0.0f), 0.5f);
           pshare_boundingbox = prm_boundingcircle->addResource(resource_name, pbounding_circle);
        }

        GameObject::setRigidBody(new RigidBody(pshare_boundingbox));
    }
}

/**
 * @brief Destructor
 *
 */
SpriteObject::~SpriteObject()
{
}


/**
 * @brief Update function
 *
 * @param milliseconds  Time elapsed since the last call (in milliseconds)
 *
 */
void SpriteObject::update(f32 milliseconds)
{
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
void SpriteObject::render(const GLSLProgram &program, const glm::mat3 & model,
        const glm::mat3 &view) const
{
    glm::mat3 toparent;
    moveable_.getToParentTransformation(toparent);

    glm::mat3 new_model = model * toparent;

    pmesh_instance_->render(program, new_model, view);
}


} /* namespace JU */
