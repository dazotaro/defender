/*
 * Texture.cpp
 *
 *  Created on: Nov 9, 2015
 *      Author: jusabiaga
 */

// Local includes
#include "Texture.hpp"
#include "ImageHelper.hpp"  // imageInvertVertically
// Global includes
#include <SOIL/SOIL.h>           // SOIL_load_image
#include <cstdio>           // std::printf
#include <cstdlib>          // exit

namespace JU
{


Texture::Texture() : tex_id_(0)
{
}


Texture::Texture(const char* filename) : tex_id_(0)
{
    loadTexture(filename);
}

Texture::~Texture()
{
}


bool Texture::loadTexture(const char* filename)
{
    if (tex_id_)
    {
        gl::DeleteTextures(1, &tex_id_);
    }

    gl::GenTextures(1, &tex_id_);

    int width, height, channels;
    unsigned char *image = SOIL_load_image(filename, &width, &height, &channels, SOIL_LOAD_AUTO);

    if (!image)
    {
        std::printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
        std::exit(EXIT_FAILURE);
    }

    std::printf("%s: %s: number of channels = %i\n", __PRETTY_FUNCTION__, filename, channels);

    GLuint mode;

    switch (channels)
    {
        case 3:
            mode = gl::RGB;
            break;

        case 4:
            mode = gl::RGBA;
            break;

        default:
            std::printf("Loading \"%s\": number or channels %i not supported\n", filename, channels);
            std::exit(0);
    }

    // Flip the image vertically
    JU::imageInvertVertically(width, height, channels, image);

    gl::BindTexture(gl::TEXTURE_2D, tex_id_);
    gl::TexImage2D(gl::TEXTURE_2D, 0, mode, width, height, 0, mode, gl::UNSIGNED_BYTE, image);

    GLfloat filtering_mode = gl::NEAREST;


    //GLfloat filtering_mode = gl::LINEAR_MIPMAP_LINEAR;
    //glGenerateMipmap(gl::TEXTURE_2D);


    gl::TexParameterf(gl::TEXTURE_2D, gl::TEXTURE_MAG_FILTER, filtering_mode);
    gl::TexParameterf(gl::TEXTURE_2D, gl::TEXTURE_MIN_FILTER, filtering_mode);

    /*
    float color[] = { 1.0f, 0.0f, 1.0f, 1.0f };
    gl::TexParameterfv(gl::TEXTURE_2D, gl::TEXTURE_BORDER_COLOR, color);

    gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_WRAP_S, gl::REPEAT);
    gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_WRAP_T, gl::REPEAT);
    */

    SOIL_free_image_data(image);

    return true;
}

} /* namespace JU */
