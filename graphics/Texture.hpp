/*
 * Texture.hpp
 *
 *  Created on: Nov 9, 2015
 *      Author: jusabiaga
 */

#ifndef TEXTURE_HPP_
#define TEXTURE_HPP_

#include "gl_core_4_2.hpp"  // GLuint

namespace JU
{

class Texture
{
    public:
        Texture();
        Texture(const char* filename);
        virtual ~Texture();

        bool loadTexture(const char* filename);
        inline GLuint getTextureId() const { return tex_id_; }

    private:
        GLuint tex_id_;
};

} /* namespace JU */

#endif /* TEXTURE_HPP_ */
