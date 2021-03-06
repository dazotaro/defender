

// Local includes
#include "GLSLProgram.hpp"    		// GLSLProgram
#include "GLSLProgramHelper.hpp"	// fileExists


// Global includes
#include <fstream>
#include <sstream>
#include <iostream>

namespace JU
{

// MACROS
#define DEBUG 0


// CONST AND STATIC
#if DEBUG
    static std::ostream &debug = std::cout;
#else
    static std::ostringstream debug;
#endif // DEBUG

const std::string GLSLProgram::COLOR_TEX_PREFIX ("ColorTex");
const std::string GLSLProgram::NORMAL_MAP_TEX_PREFIX ("NormalMapTex");


/**
 * Default constructor
 */
GLSLProgram::GLSLProgram() : handle_(0), linked_(false) {}


/**
 * Compile a shader file
 *
 * @param filename 	Name of the file
 * @param type		Shader type
 * @return True if successful, false otherwise
 */
bool GLSLProgram::compileShaderFromFile(const char * fileName, GLSLShader::GLSLShaderType type)
{
    if (!GLSLProgramHelper::fileExists(fileName))
    {
        log_string_ = "File not found.";
        return false;
    }

    if (handle_ <= 0)
    {
        handle_ = gl::CreateProgram();
        if( handle_ == 0)
        {
            log_string_ = "Unable to create shader program.";
            return false;
        }
    }

    std::printf("Compiling file %s\n", fileName);

    std::ifstream inFile( fileName, std::ios::in );
    if (!inFile)
    {
        return false;
    }

    std::ostringstream code;
    while (inFile.good())
    {
        JU::int32 c = inFile.get();
        if (!inFile.eof())
            code << (char) c;
    }
    inFile.close();

    return compileShaderFromString(code.str(), type);
}


/**
 * Compile shader from string
 *
 * @param source String containing the shader code
 * @param type	 Type of the shader (fragment, vertex...)
 * @return True if successful, false otherwise
 */
bool GLSLProgram::compileShaderFromString(const std::string & source, GLSLShader::GLSLShaderType type)
{
    if (handle_ <= 0)
    {
        handle_ = gl::CreateProgram();
        if (handle_ == 0)
        {
            log_string_ = "Unable to create shader program.";
            return false;
        }
    }

    GLuint shaderhandle_ = 0;

    switch (type)
    {
        case GLSLShader::VERTEX:
            shaderhandle_ = gl::CreateShader(gl::VERTEX_SHADER);
            break;
        case GLSLShader::FRAGMENT:
            shaderhandle_ = gl::CreateShader(gl::FRAGMENT_SHADER);
            break;
        case GLSLShader::GEOMETRY:
            shaderhandle_ = gl::CreateShader(gl::GEOMETRY_SHADER);
            break;
        case GLSLShader::TESS_CONTROL:
            shaderhandle_ = gl::CreateShader(gl::TESS_CONTROL_SHADER);
            break;
        case GLSLShader::TESS_EVALUATION:
            shaderhandle_ = gl::CreateShader(gl::TESS_EVALUATION_SHADER);
            break;
        default:
            return false;
    }

    const char * c_code = source.c_str();
    gl::ShaderSource(shaderhandle_, 1, &c_code, NULL);

    // Compile the shader
    gl::CompileShader(shaderhandle_ );

    // Check for errors
    JU::int32 result;
    gl::GetShaderiv(shaderhandle_, gl::COMPILE_STATUS, &result);
    if (gl::FALSE_ == result)
    {
        // Compile failed, store log and return false
        JU::int32 length = 0;
        log_string_ = "";
        gl::GetShaderiv(shaderhandle_, gl::INFO_LOG_LENGTH, &length);
        if (length > 0)
        {
            char * c_log = new char[length];
            JU::int32 written = 0;
            gl::GetShaderInfoLog(shaderhandle_, length, &written, c_log);
            log_string_ = c_log;
            delete [] c_log;
        }

        return false;
    }
    else
    {
        // Compile succeeded, attach shader and return true
        gl::AttachShader(handle_, shaderhandle_);
        return true;
    }
}


/**
 * Link the shader program
 *
 * @return True is successful, false otherwise
 */
bool GLSLProgram::link()
{
    if( linked_ ) return true;
    if( handle_ <= 0 ) return false;

    gl::LinkProgram(handle_);

    GLint status = 0;
    gl::GetProgramiv( handle_, gl::LINK_STATUS, &status);
    if (gl::FALSE_ == status)
    {
        // Store log and return false
        GLint length = 0;
        log_string_ = "";

        gl::GetProgramiv(handle_, gl::INFO_LOG_LENGTH, &length );

        if (length > 0)
        {
            char * c_log = new char[length];
            GLint written = 0;
            gl::GetProgramInfoLog(handle_, length, &written, c_log);
            log_string_ = c_log;
            delete [] c_log;
        }

        return false;
    }
    else
    {
        linked_ = true;
        return linked_;
    }
}


/**
 * Enable the shader program
 */
void GLSLProgram::use() const
{
    if(handle_ <= 0 || (!linked_))
        return;

    gl::UseProgram(handle_);
}


/**
 * Return log string
 *
 * @return Log string
 */
std::string GLSLProgram::log() const
{
    return log_string_;
}


/**
 * Get program handle
 *
 * @return Program handle
 */
GLuint GLSLProgram::getHandle() const
{
    return handle_;
}


/**
 * Is program successfully linked?
 *
 * @return True if sucessful, false otherwise
 */
bool GLSLProgram::isLinked() const
{
    return linked_;
}


/**
 * Wrapper around GL function call:
 *
 * "Associates a generic vertex attribute index with a named attribute variable"
 *
 * @param location 	Location
 * @param name		Name of the attribute
 */
void GLSLProgram::bindAttribLocation(GLuint location, const char * name)
{
    gl::BindAttribLocation(handle_, location, name);
}


/**
 * Wrapper around GL function call:
 *
 * "Bind a user-defined varying out variable to a fragment shader color number"
 *
 * @param location 	Location
 * @param name		Name of the attribute
 */
void GLSLProgram::bindFragDataLocation(GLuint location, const char * name)
{
    gl::BindFragDataLocation(handle_, location, name);
}


/**
 * Wrapper around GL function call to set a uniform
 *
 * @param name Uniform name
 * @param x	   x value
 * @param y	   y value
 * @param z	   z value
 */
void GLSLProgram::setUniform(const char* name, float x, float y, float z) const
{
    GLint loc = getUniformLocation(name);

    if (loc >= 0)
    {
        gl::Uniform3f(loc,x,y,z);
    }
    else
    {
        debug << "Uniform: " << name << " not found." << std::endl;
    }
}



/**
 * Wrapper around GL function call to set a uniform
 *
 * @param name Uniform name
 * @param v	   Vec3
 */
void GLSLProgram::setUniform(const char* name, const glm::vec3 & v) const
{
    this->setUniform(name,v.x,v.y,v.z);
}



/**
 * Wrapper around GL function call to set a uniform
 *
 * @param name Uniform name
 * @param v	   Vec4
 */
void GLSLProgram::setUniform(const char* name, const glm::vec4 & v) const
{
    GLint loc = getUniformLocation(name);

    if (loc >= 0)
    {
        gl::Uniform4f(loc,v.x,v.y,v.z,v.w);
    }
    else
    {
        debug << "Uniform: " << name << " not found." << std::endl;
    }
}



/**
 * Wrapper around GL function call to set a uniform
 *
 * @param name Uniform name
 * @param m	   Mat4
 */
void GLSLProgram::setUniform(const char* name, const glm::mat4 & m) const
{
    GLint loc = getUniformLocation(name);

    if (loc >= 0)
    {
        gl::UniformMatrix4fv(loc, 1, gl::FALSE_, &m[0][0]);
    }
    else
    {
        debug << "Uniform: " << name << " not found." << std::endl;
    }
}



/**
 * Wrapper around GL function call to set a uniform
 *
 * @param name Uniform name
 * @param m	   Mat3
 */
void GLSLProgram::setUniform(const char* name, const glm::mat3 & m) const
{
    GLint loc = getUniformLocation(name);

    if (loc >= 0)
    {
        gl::UniformMatrix3fv(loc, 1, gl::FALSE_, &m[0][0]);
    }
    else
    {
        debug << "Uniform: " << name << " not found." << std::endl;
    }
}



/**
 * Wrapper around GL function call to set a uniform
 *
 * @param name Uniform name
 * @param val  Floating point value
 */
void GLSLProgram::setUniform(const char* name, float val) const
{
    GLint loc = getUniformLocation(name);

    if (loc >= 0)
    {
        gl::Uniform1f(loc, val);
    }
    else
    {
        debug << "Uniform: " << name << " not found." << std::endl;
    }
}



/**
 * Wrapper around GL function call to set a uniform
 *
 * @param name Uniform name
 * @param val  Integer value
 */
void GLSLProgram::setUniform(const char* name, JU::int32 val) const
{
    GLint loc = getUniformLocation(name);

    if (loc >= 0)
    {
        gl::Uniform1i(loc, val);
    }
    else
    {
        debug << "Uniform: " << name << " not found." << std::endl;
    }
}



/**
 * Wrapper around GL function call to set a uniform
 *
 * @param name Uniform name
 * @param val  Boolean value
 */
void GLSLProgram::setUniform(const char* name, bool val) const
{
    GLint loc = getUniformLocation(name);

    if (loc >= 0)
    {
        gl::Uniform1i(loc, val);
    }
    else
    {
        debug << "Uniform: " << name << " not found." << std::endl;
    }
}


/**
 * Print active uniform variables
 */
void GLSLProgram::printActiveUniforms()  const
{
    GLint nUniforms, size, location, maxLen;
    GLchar * name;
    GLsizei written;
    GLenum type;

    gl::GetProgramiv(handle_, gl::ACTIVE_UNIFORM_MAX_LENGTH, &maxLen);
    gl::GetProgramiv(handle_, gl::ACTIVE_UNIFORMS, &nUniforms);

    name = (GLchar *) malloc( maxLen );

    printf(" Location | Name\n");
    printf("------------------------------------------------\n");
    for (JU::int32 i = 0; i < nUniforms; ++i)
    {
        gl::GetActiveUniform( handle_, i, maxLen, &written, &size, &type, name );
        location = gl::GetUniformLocation(handle_, name);
        printf(" %-8d | %s\n",location, name);
    }

    free(name);
}


/**
 * Print active attribute values
 */
void GLSLProgram::printActiveAttribs() const
{

    GLint written, size, location, maxLength, nAttribs;
    GLenum type;
    GLchar * name;

    gl::GetProgramiv(handle_, gl::ACTIVE_ATTRIBUTE_MAX_LENGTH, &maxLength);
    gl::GetProgramiv(handle_, gl::ACTIVE_ATTRIBUTES, &nAttribs);

    name = (GLchar *) malloc( maxLength );

    printf(" Index | Name\n");
    printf("------------------------------------------------\n");
    for (JU::int32 i = 0; i < nAttribs; i++)
    {
        gl::GetActiveAttrib( handle_, i, maxLength, &written, &size, &type, name );
        location = gl::GetAttribLocation(handle_, name);
        printf(" %-5d | %s\n",location, name);
    }

    free(name);
}


/**
 * Is this shader program valid?
 *
 * @return True is valid, false otherwise
 */
bool GLSLProgram::validate()
{
    if (!isLinked())
        return false;

    GLint status;
    gl::ValidateProgram( handle_ );
    gl::GetProgramiv( handle_, gl::VALIDATE_STATUS, &status );

    if (gl::FALSE_ == status)
    {
        // Store log and return false
        int length = 0;
        log_string_ = "";

        gl::GetProgramiv(handle_, gl::INFO_LOG_LENGTH, &length );

        if (length > 0)
        {
            char * c_log = new char[length];
            JU::int32 written = 0;
            gl::GetProgramInfoLog(handle_, length, &written, c_log);
            log_string_ = c_log;
            delete [] c_log;
        }

        return false;
    }
    else
    {
       return true;
    }
}



/**
 * Get uniform location
 *
 * @param name Uniform name
 * @return Uniform location
 */
GLint GLSLProgram::getUniformLocation(const char * name) const
{
    return gl::GetUniformLocation(handle_, name);
}


} // namespace JU
