/*
 * ParticleSystem.hpp
 *
 *  Created on: Nov 20, 2015
 *      Author: jusabiaga
 */

#ifndef PARTICLESYSTEM_HPP_
#define PARTICLESYSTEM_HPP_

// Local includes
#include "../graphics/Renderable2DInterface.hpp"    // Renderable2DInterface

namespace JU
{

template <uint32 MAX_PARTICLES>
class ParticleSystem : public Renderable2DInterface
{
    public:
        ParticleSystem();
        virtual ~ParticleSystem();

        void init();
        void terminate();

        void addParticle(const glm::vec2& position,
                         const glm::vec2& velocity,
                         f32 mass,
                         f32 kf,
                         f32 viscosity_threshold,
                         uint32 time,
                         const glm::vec4& color);
        void update(uint32 milliseconds);
        void render(const GLSLProgram &program, const glm::mat3 & model, const glm::mat3 &view) const override;

    private:

        // Type definitions
        struct Particle
        {
            glm::vec2 velocity_;                //!< Velocity
            f32       mass_;                    //!< Particle's mass
            f32       kf_;                      //!< Friction coefficient
            f32       viscosity_threshold_;     //!< Speed at which the model of the viscosity switches from linear to quadratic
            int32     time_;                    //!< Particle's lifetime (in milliseconds)
        };

        // General
        bool initialized_;                      //!< Has the system been initialized?
        // Physics Simulation
        glm::vec2 ppositions_[MAX_PARTICLES];   //!< 2D position
        glm::vec4 pcolors_[MAX_PARTICLES];      //!< 2D position
        Particle  pparticles_[MAX_PARTICLES];   //!< Physics-related particle data
        uint32    particle_count_;
        // OpenGL
        GLuint   vao_;
        GLuint   pvbos_[2];
        Shareable<const Texture>*   pshare_texture_;
};

} /* namespace JU */

#include "ParticleSystem.cpp"

#endif /* PARTICLESYSTEM_HPP_ */
