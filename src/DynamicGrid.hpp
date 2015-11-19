/*
 * DynamicGrid.hpp
 *
 *  Created on: Nov 12, 2015
 *      Author: jusabiaga
 */

#ifndef DYNAMICGRID_HPP_
#define DYNAMICGRID_HPP_

// Local includes
#include "../graphics/Renderable2DInterface.hpp"    // Renderable2DInterface
#include "../graphics/GLMesh2D.hpp"                 // GLMesh2D
#include "GridMesh.hpp"                             // GridMesh
#include "../core/Moveable2D.hpp"                   // Moveable2D

namespace JU
{

template <uint32 SIZEX, uint32 SIZEY>
class DynamicGrid : public Renderable2DInterface
{
        // Static Constants
        static const uint8 NUM_VBOS = 2;

    public:
        explicit DynamicGrid(Moveable2D moveable, f32 mass, const glm::vec4& color);
        virtual ~DynamicGrid();

    public:
        // Getters
        const Moveable2D& getMoveable() const;
        Moveable2D& getMoveable();

        // Setters
        void setPosition(f32 x, f32 y);
        void update(JU::f32 milliseconds, const glm::vec2* force_locations = nullptr, uint32 num_forces = 0);
        void render(const GLSLProgram &program, const glm::mat3 & model, const glm::mat3 &view) const override;

    private:
        Moveable2D  moveable_;
        f32         mass_;                              //!< Mass of all particles
        glm::vec2   pvertices_[SIZEX * SIZEY];          //!< Particle coordinates
        glm::vec2   pvelocities_[SIZEX * SIZEY];         //!< Particle velocities
        glm::vec2   pforces_[SIZEX * SIZEY];             //!< Particle force accumulators
        uint32      pindices_[2 * ( (SIZEX-1)*SIZEY + SIZEX*(SIZEY-1) )];   //!< Mesh indices
        GLuint      vao_;
        GLuint      pvbos_[NUM_VBOS];
        glm::vec4   color_;
};

} /* namespace JU */

#include "DynamicGrid.cpp"

#endif /* DYNAMICGRID_HPP_ */
