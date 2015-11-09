/*
 * TextureManager.cpp
 *
 *  Created on: Nov 9, 2015
 *      Author: jusabiaga
 */

#include "TextureManager.hpp"

namespace JU
{


TextureManager::TextureManager() : num_tex_bound_(0)
{
    // TODO Auto-generated constructor stub

}


TextureManager::~TextureManager()
{
}


GLuint TextureManager::bindTexture(GLuint tex_id)
{
    gl::ActiveTexture(gl::TEXTURE0 + num_tex_bound_);
    gl::BindTexture(gl::TEXTURE_2D, tex_id);

    return num_tex_bound_++;
}


void TextureManager::unbindAllTextures()
{
    num_tex_bound_ = 0;
}


} /* namespace JU */
