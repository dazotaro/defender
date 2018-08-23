/*
 * TextureManager.hpp
 *
 *  Created on: Nov 9, 2015
 *      Author: jusabiaga
 */

#ifndef TEXTUREMANAGER_HPP_
#define TEXTUREMANAGER_HPP_

#include "gl_core_4_2.hpp"      // GLuint

namespace JU
{

/**
 * Class to facilitate the management of textures
 */
class TextureManager
{
    template <typename U>
    friend class Singleton;

    protected:
        TextureManager();
        virtual ~TextureManager();

        TextureManager(const TextureManager& rhs) { num_tex_bound_ = rhs.num_tex_bound_; }
        TextureManager& operator=(const TextureManager& rhs);

    public:
        GLuint bindTexture(GLuint tex_id);
        void unbindAllTextures();

    private:
        GLuint num_tex_bound_;		//!< Number of textures bound
};

} /* namespace JU */

#endif /* TEXTUREMANAGER_HPP_ */
