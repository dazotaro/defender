/*
 * DynamicGridObject.cpp
 *
 *  Created on: Nov 12, 2015
 *      Author: jusabiaga
 */

#include "DynamicGridObject.hpp"
#include "../graphics/GLMesh2DInstance.hpp" // GLMesh2DInstance
#include "../graphics/GLMesh2D.hpp"         // GLMesh2D
#include "../core/Keyboard.hpp"             // Keyboard
#include "../core/Singleton.hpp"            // Singleton
#include "../core/Moveable2D.hpp"           // Moveable2D
#include "GridMesh.hpp"                     // GridMesh
#include "../core/Singleton.hpp"            // Singleton
#include "../core/ResourceManager.hpp"      // ResourceManager
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
DynamicGridObject::DynamicGridObject(const char* name, uint32 sizex, uint32 sizey)
{
    GameObject::setName(std::string(name));

    const std::string resource_name(GridMesh::getId());

    // GLMesh2D
    // -------------
    ResourceManager<const GLMesh2D>* prm_glmesh = Singleton<ResourceManager<const GLMesh2D>>::getInstance();

    const GridMesh mesh(sizex, sizey);
    Shareable<const GLMesh2D>* pshare_mesh;
    if (!(pshare_mesh = prm_glmesh->referenceResource(resource_name)))
    {
        GLMesh2D* pglmesh = new GLMesh2D();
        pglmesh->init(mesh, gl::DYNAMIC_DRAW);
        pshare_mesh = prm_glmesh->addResource(resource_name, pglmesh);
    }

    // GLMesh2DInstance
    // ----------------
    GameObject::pmesh_instance_ = new GLMesh2DInstance(pshare_mesh);
    pmesh_instance_->setColor(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
}

/**
 * @brief Destructor
 *
 */
DynamicGridObject::~DynamicGridObject()
{
}


/**
 * @brief Update function
 *
 * @param milliseconds  Time elapsed since the last call (in milliseconds)
 *
 */
void DynamicGridObject::update(f32 milliseconds)
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
void DynamicGridObject::render(const GLSLProgram &program, const glm::mat3 & model,
        const glm::mat3 &view) const
{
    glm::mat3 toparent;
    moveable_.getToParentTransformation(toparent);

    glm::mat3 new_model = model * toparent;

    pmesh_instance_->render(program, new_model, view);
}


} /* namespace JU */
