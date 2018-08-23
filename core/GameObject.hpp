/*
 * GameObject.hpp
 *
 *  Created on: Oct 21, 2015
 *      Author: jusabiaga
 */

#ifndef GAMEOBJECT_HPP_
#define GAMEOBJECT_HPP_

// Local include
#include "Defs.hpp"         // JU::f32
#include "Moveable2D.hpp"   // Moveable2D
// Global include
#include <glm/glm.hpp>      // mat3
#include <string>           // std::string

namespace JU
{

// Forward Declarations
class GLMesh2DInstance;
class GLSLProgram;
class RigidBody;

/**
 * Base class for game objects
 */
class GameObject
{
    public:
        GameObject();
        GameObject(const std::string& name, GLMesh2DInstance* pmesh_instance, Moveable2D moveable, RigidBody* prigid_body = nullptr, bool collideable = false);
        virtual ~GameObject();

        // Getters
        const std::string& getName() const;
        const GLMesh2DInstance* getMeshInstance() const;
        RigidBody* getRigidBody() const;
        const Moveable2D& getMoveable() const;
        Moveable2D& getMoveable();

        // Setters
        void setName(const std::string& name);
        void setMeshInstance(GLMesh2DInstance* pmesh_instance);
        void setMoveable2D(Moveable2D moveable);
        void setRigidBody(RigidBody* prigid_body);
        void setCollideable(bool collideable);

        virtual void update(JU::f32 milliseconds) = 0;
        virtual void render(const GLSLProgram &program, const glm::mat3 & model, const glm::mat3 &view) const;

    protected:
        std::string       name_;			//!< Name of the object
        GLMesh2DInstance* pmesh_instance_;  //!< Renderable component
        Moveable2D        moveable_;        //!< Position and orientation
        RigidBody*        prigid_body_;     //!< RigidBody
        bool              collideable_;		//!< Is it collideable?
};

} /* namespace JU */

#endif /* GAMEOBJECT_HPP_ */
