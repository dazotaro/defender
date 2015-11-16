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

class DynamicGrid : public Renderable2DInterface
{
    public:
        explicit DynamicGrid(Moveable2D moveable, uint32 sizex, uint32 sizey, const glm::vec4& color);
        virtual ~DynamicGrid();

    public:
        void update(JU::f32 milliseconds);
        void render(const GLSLProgram &program, const glm::mat3 & model, const glm::mat3 &view) const override;

    private:
        Moveable2D  moveable_;
        GridMesh    mesh_;
        GLMesh2D    glmesh_;
        glm::vec4   color_;
};

} /* namespace JU */

#endif /* DYNAMICGRID_HPP_ */
