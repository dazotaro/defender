/*
 * GLSLProgramHelper.cpp
 *
 *  Created on: Oct 18, 2015
 *      Author: jusabiaga
 */

#include "GLSLProgramHelper.hpp"

namespace JU
{

namespace GLSLProgramHelper
{
    GLSLProgram compileAndLinkShader(const char* vertex, const char* fragment)
    {
        GLSLProgram program;

        if (!program.compileShaderFromFile(vertex, GLSLShader::VERTEX))
        {
            printf("Vertex shader failed to compile!\n%s", program.log().c_str());
            exit(1);
        }
        if (!program.compileShaderFromFile(fragment, GLSLShader::FRAGMENT))
        {
            printf("Fragment shader failed to compile!\n%s", program.log().c_str());
            exit(1);
        }
        if (!program.link())
        {
            printf("Shader program failed to link!\n%s", program.log().c_str());
            exit(1);
        }

        program.use();

        return program;
    }
}

}
