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
DynamicGridObject::DynamicGridObject(const char* name, uint32 sizex, uint32 sizey) : mesh_(sizex, sizey)
{
    GameObject::setName(std::string(name));

    const std::string resource_name(GridMesh::getId());

    // GLMesh2D
    // -------------
    ResourceManager<const GLMesh2D>* prm_glmesh = Singleton<ResourceManager<const GLMesh2D>>::getInstance();

    //mesh_ = GridMesh(sizex, sizey);
    Shareable<const GLMesh2D>* pshare_mesh;
    if (!(pshare_mesh = prm_glmesh->referenceResource(resource_name)))
    {
        GLMesh2D* pglmesh = new GLMesh2D();
        pglmesh->transferDataGPU(mesh_, gl::DYNAMIC_DRAW);
        pshare_mesh = prm_glmesh->addResource(resource_name, pglmesh);
    }

    // GLMesh2DInstance
    // ----------------
    GameObject::pmesh_instance_ = new GLMesh2DInstance(pshare_mesh);
    pmesh_instance_->setColor(glm::vec4(0.0f, 0.5f, 1.0f, 1.0f));
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
    glm::vec2* pvertices = nullptr;
    uint32 num_vertices = 0;
    mesh_.getVertexCoordinates(pvertices, num_vertices);

    if (num_vertices)
    {
        glm::vec2 origin(0.0f, 0.0f);
        f32 max_displacement = 2.0f;
        f32 range = 10.0f;
        f32 slope = max_displacement / range;

        for (uint32 i = 0; i < num_vertices; ++i)
        {
            glm::vec2 vertex(pvertices[i]);
            glm::vec2 dir(glm::normalize(vertex));

            f32 radius = std::sqrt((vertex[0] - origin[0])*(vertex[0] - origin[0]) + (vertex[1] - origin[1])*(vertex[1] - origin[1]));

            if (radius < range)
            {
                f32 displacement = max_displacement - radius * slope;
                vertex += displacement * dir;
            }

            pvertices[i] = vertex;
        }
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
void DynamicGridObject::render(const GLSLProgram &program, const glm::mat3 & model,
        const glm::mat3 &view) const
{
    glm::mat3 toparent;
    moveable_.getToParentTransformation(toparent);

    glm::mat3 new_model = model * toparent;

    pmesh_instance_->render(program, new_model, view);
}


} /* namespace JU */
