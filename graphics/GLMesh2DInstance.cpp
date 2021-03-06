/*
 * GLMesh2DInstance.cpp
 *
 *  Created on: Oct 19, 2015
 *      Author: jusabiaga
 */

#include "GLMesh2DInstance.hpp"
#include "GLMesh2D.hpp"                 // GLMesh2D
#include "GLSLProgram.hpp"              // GLSLProgram
#include "TextureManager.hpp"           // TextureManager
#include "../core/Singleton.hpp"        // Singleton
#include "../core/ResourceManager.hpp"  // ResourceManager, Shareable

namespace JU
{

/**
 * Non-default constructor
 *
 * @param pshare_mesh 		(shareable) Address of mesh
 * @param pshare_texture	(shareable) Address of texture
 * @param color				Color
 */
GLMesh2DInstance::GLMesh2DInstance(Shareable<const GLMesh2D>* pshare_mesh,
                                   Shareable<const Texture>* pshare_texture,
                                   const glm::vec4& color)
                    : pshare_mesh_(pshare_mesh), pshare_texture_(pshare_texture), color_(color)
{
}


/**
 * Destructor
 */
GLMesh2DInstance::~GLMesh2DInstance()
{
    if (pshare_mesh_)
        Singleton<ResourceManager<const GLMesh2D>>::getInstance()->releaseResource(pshare_mesh_);
    if (pshare_texture_)
        Singleton<ResourceManager<const Texture>>::getInstance()->releaseResource(pshare_texture_);
}


/**
 * Get Mesh
 *
 * @return Address of GLMesh2D object
 */
const GLMesh2D* GLMesh2DInstance::getGLMesh() const
{
    return pshare_mesh_->pdata_;
}


/**
 * Set Color
 *
 * @param color Color
 */
void GLMesh2DInstance::setColor(const glm::vec4& color)
{
    color_ = color;
}


/**
 * Render instance
 *
 * @param program 	Shader program
 * @param model 	Homogeneous model matrix
 * @param view		Homogeneous view matrix
 */
void GLMesh2DInstance::render(const GLSLProgram &program, const glm::mat3 & model, const glm::mat3 &view) const
{
    glm::mat3 MV = view * model;

    // LOAD UNIFORMS
    program.setUniform("M", model);
    program.setUniform("MV", MV);
    program.setUniform("color", color_);
    if (pshare_texture_)
        program.setUniform("tex_image", static_cast<int>(JU::Singleton<TextureManager>::getInstance()->bindTexture(pshare_texture_->pdata_->getTextureId())));

    // Tell the GLMesh2D to render
    pshare_mesh_->pdata_->render();
}

} /* namespace JU */
