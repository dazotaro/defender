/*
 * GLSLProgramHelper.cpp
 *
 *  Created on: Oct 18, 2015
 *      Author: jusabiaga
 */

#include "GLSLProgramHelper.hpp"
#include <sys/stat.h>				// stat

namespace JU
{

namespace GLSLProgramHelper
{

/**
 * Compile and link a shader program
 *
 * @param vertex 	Vertex shader filename
 * @param fragment	Fragment shader filename
 * @return GLSLProgram if successful, it will exit otherwise
 */
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


/**
 * Does this file exist?
 *
 * @return True if it does, false otherwise
 */
bool fileExists( const std::string & fileName )
{
    struct stat info;
    JU::int32 ret = -1;

    ret = stat(fileName.c_str(), &info);
    return 0 == ret;
}

} // namespace GLSLProgramHelper

}
