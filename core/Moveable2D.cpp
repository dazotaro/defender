/*
 * Moveable2D.cpp
 *
 *  Created on: Oct 19, 2015
 *      Author: jusabiaga
 */

#include <cmath>    // cosf, sinf
#include "Moveable2D.hpp"

namespace JU
{

/**
* @brief Constructor
*
* @detail Constructor
*
* @param posx   Position's X coordinate
* @param posy   Position's Y coordinate
* @param angle  Orientation angle in radians
* @param scalex X axis scale factor
* @param scaley Y axis scale factor
*
*/
Moveable2D::Moveable2D(JU::f32 posx, JU::f32 posy, JU::f32 angle, JU::f32 scalex, JU::f32 scaley)
        : position_(posx, posy), angle_(angle), scale_(scalex, scaley)
{
}


/**
* @brief Transformation to this' parents coordinate system
*
* @detail Transformation to this' parents coordinate system. If Moveable2D represents a the position and orientation
*         of a game object, this functions returns the Model matrix to the parent's coordinate system
*
* @param to_parent  3x3 matrix in homogeneous coordinates with resulting transformation
*
*/
void Moveable2D::getToParentTransformation(glm::mat3& to_parent) const
{
    JU::f32 cosine = std::cos(angle_);
    JU::f32 sine   = std::sin(angle_);

    to_parent[0][0] = scale_[0] * cosine; to_parent[1][0] = scale_[1] *  -sine; to_parent[2][0] = position_[0];
    to_parent[0][1] = scale_[0] *   sine; to_parent[1][1] = scale_[1] * cosine; to_parent[2][1] = position_[1];
    to_parent[0][2] =               0.0f; to_parent[1][2] =               0.0f; to_parent[2][2] =         1.0f;
}


/**
* @brief Transformation from this' parent's coordinate system
*
* @detail Transformation from this' parent's coordinate system. If Moveable2D represents the position and orientation
*         of a camera, this functions returns the View matrix.
*
* @param to_parent  3x3 matrix in homogeneous coordinates with resulting transformation
*
*/
void Moveable2D::getFromParentTransformation(glm::mat3& from_parent) const
{
    JU::f32 cosine = std::cos(angle_);
    JU::f32 sine   = std::sin(angle_);
    JU::f32 inv_scalex  = 1.0f / scale_[0];
    JU::f32 inv_scaley  = 1.0f / scale_[1];

    from_parent[0][0] = cosine * inv_scalex;
    from_parent[1][0] =   sine * inv_scalex;
    from_parent[2][0] = -position_[0] * cosine * inv_scalex - position_[1] * sine * inv_scalex;

    from_parent[0][1] =  -sine * inv_scaley;
    from_parent[1][1] = cosine * inv_scaley;
    from_parent[2][1] =  position_[0] * sine * inv_scaley  - position_[1] * cosine * inv_scaley;

    from_parent[0][2] = 0.0f;
    from_parent[1][2] = 0.0f;
    from_parent[2][2] = 1.0f;
}


/**
* @brief Move this Moveable2D along its X axis
*
* @detail Translates 'this' along the X axis by 'distance'
*
* @param distance Distance to translate
*
*/
void Moveable2D::moveX(JU::f32 distance)
{
    position_[0] += distance * std::cos(angle_);
    position_[1] += distance * std::sin(angle_);
}


/**
* @brief Move this Moveable2D along its Y axis
*
* @detail Translates 'this' along the Y axis by 'distance'
*
* @param distance Distance to translate
*
*/
void Moveable2D::moveY(JU::f32 distance)
{
    position_[0] -= distance * std::sin(angle_);
    position_[1] += distance * std::cos(angle_);
}


/**
* @brief Rotate 'this' Moveable2D
*
* @detail Rotates 'this'
*
* @param angle In radians
*
*/
void Moveable2D::rotate(JU::f32 angle)
{
    angle_ += angle;
}


} /* namespace JU */
