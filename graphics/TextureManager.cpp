/*
 * TextureManager.cpp
 *
 *  Created on: Nov 9, 2015
 *      Author: jusabiaga
 */

#include "TextureManager.hpp"

namespace JU
{

/**
 * Default constructor
 */
TextureManager::TextureManager() : num_tex_bound_(0)
{
    // TODO Auto-generated constructor stub

}


/**
 * Destructor
 */
TextureManager::~TextureManager()
{
}


/**
 * Bind a texture
 *
 * @param tex_id Texture id
 * @return Active texture id
 */
GLuint TextureManager::bindTexture(GLuint tex_id)
{
    gl::ActiveTexture(gl::TEXTURE0 + num_tex_bound_);
    gl::BindTexture(gl::TEXTURE_2D, tex_id);

    return num_tex_bound_++;
}


/**
 * Unbind all textures
 */
void TextureManager::unbindAllTextures()
{
    num_tex_bound_ = 0;
}


} /* namespace JU */
