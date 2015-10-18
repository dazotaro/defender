/*
 * GLSLProgramHelper.hpp
 *
 *  Created on: Oct 18, 2015
 *      Author: jusabiaga
 */

#ifndef GLSLPROGRAMHELPER_HPP_
#define GLSLPROGRAMHELPER_HPP_

#include "GLSLProgram.hpp"		// JU::GLSLProgram

namespace JU
{

namespace GLSLProgramHelper
{
	GLSLProgram compileAndLinkShader(const char* vertex, const char* fragment);
}

}

#endif /* GLSLPROGRAMHELPER_HPP_ */
