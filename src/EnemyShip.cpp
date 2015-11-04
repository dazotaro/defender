/*
 * EnemyShip.cpp
 *
 *  Created on: Oct 21, 2015
 *      Author: jusabiaga
 */

#include "EnemyShip.hpp"
#include "../graphics/GLMesh2DInstance.hpp"	// GLMesh2DInstance
#include "../graphics/GLMesh2D.hpp"			// GLMesh2D
#include "../core/Keyboard.hpp"			// Keyboard
#include "../core/Singleton.hpp"		// Singleton
#include "../core/Moveable2D.hpp"		// Moveable2D
#include "SquareMesh.hpp"				// SquareMesh
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
EnemyShip::EnemyShip(f32 posx, f32 posy, f32 angle,
                     f32 distance, f32 angle_delta,
                     const glm::vec4& color)
            : distance_(distance), angle_delta_(angle_delta)
{
    const std::string resource_name(SquareMesh::getId());

    GameObject::setMoveable2D(Moveable2D(posx, posy, angle, 1.0f, 1.0f));

    // GLMesh2D
    // -------------
    ResourceManager<GLMesh2D>* prm_glmesh = Singleton<ResourceManager<GLMesh2D>>::getInstance();

    const SquareMesh mesh;
    ShareableResource<GLMesh2D>* pglmesh_resource;
    if (!(pglmesh_resource = prm_glmesh->referenceResource(resource_name)))
    {
        GLMesh2D* pglmesh = new GLMesh2D();
        pglmesh->init(mesh);
        pglmesh_resource = prm_glmesh->addResource(resource_name, pglmesh);
    }

    // GLMesh2DInstance
    // ----------------
    // GLMesh2DInstance
    // ----------------
    GameObject::pmesh_instance_ = new GLMesh2DInstance(pglmesh_resource, color);

    // RigidBody
    // -------------
    ResourceManager<BoundingCircle>* prm_boundingcircle = Singleton<ResourceManager<BoundingCircle>>::getInstance();

    ShareableResource<BoundingCircle>* pboundingcircle_resource;
    if (!(pboundingcircle_resource = prm_boundingcircle->referenceResource(resource_name)))
    {
       BoundingCircle* pbounding_circle = new BoundingCircle(glm::vec2(0.0f, 0.0f), 0.5f);
       pboundingcircle_resource = prm_boundingcircle->addResource(resource_name, pbounding_circle);
    }

    GameObject::setRigitBody(new RigidBody(pboundingcircle_resource));
}

/**
 * @brief Destructor
 *
 */
EnemyShip::~EnemyShip()
{
}

/**
 * @brief Update function
 *
 * @param milliseconds  Time elapsed since the last call (in milliseconds)
 *
 */
void EnemyShip::update(f32 milliseconds)
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
void EnemyShip::render(const GLSLProgram &program, const glm::mat3 & model,
        const glm::mat3 &view) const
{
    glm::mat3 toparent;
    moveable_.getToParentTransformation(toparent);

    glm::mat3 new_model = model * toparent;

    pmesh_instance_->render(program, new_model, view);
}

} /* namespace JU */
