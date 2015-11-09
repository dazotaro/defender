/*
 * Mesh.hpp
 *
 *  Created on: Oct 29, 2015
 *      Author: jusabiaga
 */

#ifndef MESH2D_HPP_
#define MESH2D_HPP_

#include "../core/Defs.hpp" // JU::uint32
#include "gl_core_4_2.hpp"  // GLenum
// Global includes
#include <glm/glm.hpp>      // glm::vec2


namespace JU
{

class Mesh2D
{
    public:
        Mesh2D();
        Mesh2D(const glm::vec2* pvertices,
               uint32           num_vertices,
               const uint32*    pindices,
               uint32           num_indices,
               const glm::vec2* ptexcoordinates,
               GLenum           draw_mode);
        virtual ~Mesh2D();

        // Getter
        void getVertices(const glm::vec2** pvertices, uint32& num_vertices) const;
        void getData(const glm::vec2** pvertices,
                     uint32&           num_vertices,
                     const uint32**    pindices,
                     uint32&           num_indices,
                     const glm::vec2** ptexcoordinates,
                     GLenum&           draw_mode) const;

        // Setter
        void setData(const glm::vec2* pvertices,
                     uint32           num_vertices,
                     const uint32*    pindices,
                     uint32           num_indices,
                     const glm::vec2* ptexcoordinates,
                     GLenum           draw_mode);

    protected:
        glm::vec2*  pvertices_;
        uint32      num_vertices_;
        uint32*     pindices_;
        uint32      num_indices_;
        glm::vec2*  ptexcoordinates_;
        GLenum      draw_mode_;         //!< GL_TRIANGLE, GL_TRIANGLE_FAN, GL_LINE, GL_LINE_LOOP
};

} /* namespace JU */

#endif /* MESH2D_HPP_ */
