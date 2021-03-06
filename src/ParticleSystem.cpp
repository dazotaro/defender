/*
 * ParticleSystem.cpp
 *
 *  Created on: Nov 20, 2015
 *      Author: jusabiaga
 */

// Local includes
#include "../graphics/GLSLProgram.hpp"  // GLSLProgram
// Global includes
#include <cassert>  // assert

namespace JU
{

glm::vec2 computeViscosityForce(f32 kf, const glm::vec2& velocity, f32 viscosity_threshold)
{
    glm::vec2 force;

    static uint32 above = 0;
    static uint32 below = 0;
    static uint32 hits = 0;

    f32 speed = glm::length(velocity);

    if (speed > viscosity_threshold)
    {
        force = kf * speed * velocity;

        above++;
        hits++;
    }
    else
    {
        force = kf * velocity;

        below++;
        hits++;
    }

    if (hits % 5000 == 0)
        std::printf("Above %i, below %i\n", above, below);

    return force;
}


template <uint32 MAX_PARTICLES>
ParticleSystem<MAX_PARTICLES>::ParticleSystem() : initialized_(false), particle_count_(0), vao_(0), pshare_texture_(nullptr)
{
    memset(ppositions_, 0, sizeof(ppositions_));
    memset(pparticles_, 0, sizeof(pparticles_));
    memset(pcolors_,    0, sizeof(pcolors_));
}


template <uint32 MAX_PARTICLES>
ParticleSystem<MAX_PARTICLES>::~ParticleSystem()
{
    if (initialized_)
        terminate();
}


template <uint32 MAX_PARTICLES>
void ParticleSystem<MAX_PARTICLES>::terminate()
{
    // Release Texture
    if (pshare_texture_)
        Singleton<ResourceManager<const Texture>>::getInstance()->releaseResource(pshare_texture_);

    gl::DeleteVertexArrays(1, &vao_);
    gl::DeleteBuffers(2, pvbos_);
}


template <uint32 MAX_PARTICLES>
void ParticleSystem<MAX_PARTICLES>::init()
{
    if (initialized_)
        terminate();

    // Texture
    // ----------------
    const char* texture_filename ("data/textures/sparkle_mono.png");
    ResourceManager<const Texture>* prm_texture = Singleton<ResourceManager<const Texture>>::getInstance();
    if (!(pshare_texture_ = prm_texture->referenceResource(texture_filename)))
    {
        Texture* ptexture = new Texture(texture_filename);
        pshare_texture_ = prm_texture->addResource(texture_filename, ptexture);
    }

    // Transfer the data to the GPU
    // -------------
    // VAO
    gl::GenVertexArrays(1, &vao_);
    gl::BindVertexArray(vao_);

    // VBO
    gl::GenBuffers(2, pvbos_);

    // Allocate and initialize VBO for vertex positions
    gl::BindBuffer(gl::ARRAY_BUFFER, pvbos_[0]);
    gl::BufferData(gl::ARRAY_BUFFER, sizeof(ppositions_), ppositions_, gl::DYNAMIC_DRAW);
    // Insert the VBO into the VAO
    gl::EnableVertexAttribArray(0);
    gl::VertexAttribPointer(0, 2, gl::FLOAT, gl::FALSE_, 0, 0);

    // Allocate and initialize VBO for color
    gl::BindBuffer(gl::ARRAY_BUFFER, pvbos_[1]);
    gl::BufferData(gl::ARRAY_BUFFER, sizeof(pcolors_), pcolors_, gl::DYNAMIC_DRAW);
    // Insert the VBO into the VAO
    gl::EnableVertexAttribArray(1);
    gl::VertexAttribPointer(1, 4, gl::FLOAT, gl::FALSE_, 0, 0);

    // Unbind
    gl::BindBuffer(gl::ARRAY_BUFFER, 0);
    gl::BindVertexArray(0);

    initialized_ = true;
}


template <uint32 MAX_PARTICLES>
void ParticleSystem<MAX_PARTICLES>::addParticle(const glm::vec2& position,
                                                const glm::vec2& velocity,
                                                f32 mass,
                                                f32 kf,
                                                f32 viscosity_threshold,
                                                uint32 time,
                                                const glm::vec4& color)
{
    if (particle_count_ < MAX_PARTICLES)
    {
        ppositions_[particle_count_] = position;
        pcolors_[particle_count_]    = color;
        pparticles_[particle_count_].velocity_              = velocity;
        pparticles_[particle_count_].mass_                  = mass;
        pparticles_[particle_count_].kf_                    = kf;
        pparticles_[particle_count_].viscosity_threshold_   = viscosity_threshold;
        pparticles_[particle_count_].time_                  = time;

        ++particle_count_;
    }
}


template <uint32 MAX_PARTICLES>
void ParticleSystem<MAX_PARTICLES>::update(uint32 milliseconds)
{
    f32 seconds = milliseconds * 0.001f;

    uint32 i = 0;
    while (i < particle_count_)
    {
        pparticles_[i].time_ -= milliseconds;

        // Is this particle's last frame?
        if (pparticles_[i].time_ <= 0)
        {
            ppositions_[i] = ppositions_[particle_count_ - 1];
            pcolors_[i] = pcolors_[particle_count_ - 1];
            memcpy(&pparticles_[i], &pparticles_[particle_count_ - 1], sizeof(pparticles_[0]));
            --particle_count_;
        }
        else
        {
            glm::vec2 force = -computeViscosityForce(pparticles_[i].kf_, pparticles_[i].velocity_, pparticles_[i].viscosity_threshold_);

            // Integrate
            ppositions_[i] += seconds * pparticles_[i].velocity_;
            pparticles_[i].velocity_ += seconds * force / pparticles_[i].mass_;

            ++i;
        }
    }
}


/**
 * @brief Render function
 *
 * @param program GLSL program handle (to set uniforms)
 * @param model   Model matrix to parent's coordinate system
 * @param view    Camera's view matrix (world to NDC)
 *
 */
template <uint32 MAX_PARTICLES>
void ParticleSystem<MAX_PARTICLES>::render(const GLSLProgram &program, const glm::mat3 & model, const glm::mat3 &view) const
{
    program.setUniform("V", view);

    if (pshare_texture_)
        program.setUniform("tex_image", static_cast<int>(JU::Singleton<TextureManager>::getInstance()->bindTexture(pshare_texture_->pdata_->getTextureId())));

    gl::PointSize(10);

    gl::BindVertexArray(vao_);

    // Transfer positions
    gl::BindBuffer(gl::ARRAY_BUFFER, pvbos_[0]);
    gl::BufferData(gl::ARRAY_BUFFER, sizeof(ppositions_), ppositions_, gl::DYNAMIC_DRAW);
    // Transfer colors
    gl::BindBuffer(gl::ARRAY_BUFFER, pvbos_[1]);
    gl::BufferData(gl::ARRAY_BUFFER, sizeof(pcolors_), pcolors_, gl::DYNAMIC_DRAW);

    gl::BindBuffer(gl::ARRAY_BUFFER, 0);

    // Draw using indices
    gl::DrawArrays(gl::POINTS, 0, particle_count_);

    // Unbind
    gl::BindVertexArray(0);
}


} /* namespace JU */
