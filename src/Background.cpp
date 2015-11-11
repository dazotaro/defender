/*
 * Background.cpp
 *
 *  Created on: Oct 21, 2015
 *      Author: jusabiaga
 */

#include "Background.hpp"
#include "../graphics/GLMesh2DInstance.hpp"	// GLMesh2DInstance
#include "../graphics/GLMesh2D.hpp"			// GLMesh2D
#include "../core/Keyboard.hpp"			// Keyboard
#include "../core/Singleton.hpp"		// Singleton
#include "../core/Moveable2D.hpp"		// Moveable2D
#include "SquareMesh.hpp"				// SquareMesh
#include "../core/Singleton.hpp"		// Singleton
#include "../core/ResourceManager.hpp"	// ResourceManager

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
Background::Background(f32 posx, f32 posy, f32 angle)
{
    const std::string resource_name(SquareMesh::getId());

    GameObject::setMoveable2D(Moveable2D(posx, posy, angle, 100.0f, 100.0f * 0.56f));

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
    const char* filename("./data/textures/background.jpg");
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
}

/**
 * @brief Destructor
 *
 */
Background::~Background()
{
}


/**
 * @brief Update function
 *
 * @param milliseconds  Time elapsed since the last call (in milliseconds)
 *
 */
void Background::update(f32 milliseconds)
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
void Background::render(const GLSLProgram &program, const glm::mat3 & model,
        const glm::mat3 &view) const
{
    glm::mat3 toparent;
    moveable_.getToParentTransformation(toparent);

    glm::mat3 new_model = model * toparent;

    pmesh_instance_->render(program, new_model, view);
}

} /* namespace JU */
