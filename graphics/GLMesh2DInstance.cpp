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

GLMesh2DInstance::GLMesh2DInstance(Shareable<const GLMesh2D>* pshare_mesh,
                                   Shareable<const Texture>* pshare_texture,
                                   const glm::vec4& color)
                    : pshare_mesh_(pshare_mesh), pshare_texture_(pshare_texture), color_(color)
{
}


GLMesh2DInstance::~GLMesh2DInstance()
{
    Singleton<ResourceManager<const GLMesh2D>>::getInstance()->releaseResource(pshare_mesh_);
    Singleton<ResourceManager<const Texture>>::getInstance()->releaseResource(pshare_texture_);
}


const GLMesh2D* GLMesh2DInstance::getGLMesh() const
{
    return pshare_mesh_->pdata_;
}


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
