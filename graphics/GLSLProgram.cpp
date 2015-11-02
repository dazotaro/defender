

// Local includes
#include "GLSLProgram.hpp"    // GLSLProgram


// Global includes
#include <fstream>
#include <sstream>
#include <iostream>
#include <sys/stat.h>

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


GLSLProgram::GLSLProgram() : handle_(0), linked_(false) {}



bool GLSLProgram::compileShaderFromFile(const char * fileName, GLSLShader::GLSLShaderType type)
{
    if (!fileExists(fileName))
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



void GLSLProgram::use() const
{
    if(handle_ <= 0 || (!linked_))
        return;

    gl::UseProgram(handle_);
}



std::string GLSLProgram::log() const
{
    return log_string_;
}



GLuint GLSLProgram::getHandle() const
{
    return handle_;
}



bool GLSLProgram::isLinked() const
{
    return linked_;
}



void GLSLProgram::bindAttribLocation(GLuint location, const char * name)
{
    gl::BindAttribLocation(handle_, location, name);
}



void GLSLProgram::bindFragDataLocation(GLuint location, const char * name)
{
    gl::BindFragDataLocation(handle_, location, name);
}



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



void GLSLProgram::setUniform(const char* name, const glm::vec3 & v) const
{
    this->setUniform(name,v.x,v.y,v.z);
}



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



void GLSLProgram::setSamplerUniform(const char* name)
{
    HashMapSamplerTexUnit::const_iterator iter = hmSamplerToTexUnit_.find(std::string(name));

    if (iter == hmSamplerToTexUnit_.end())
    {
        JU::int32 id = hmSamplerToTexUnit_.size() + 7;
        hmSamplerToTexUnit_[name] = id;
        setUniform(name, id);
    }
}



JU::int32 GLSLProgram::getSamplerTexUnit(const char* name) const
{
    HashMapSamplerTexUnit::const_iterator iter = hmSamplerToTexUnit_.find(std::string(name));

    if (iter == hmSamplerToTexUnit_.end())
    {
        std::printf("%s: %s: sampler %s not found\n", __FILE__, __FUNCTION__, name);
        exit(EXIT_FAILURE);
    }

    return iter->second;
}



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



GLint GLSLProgram::getUniformLocation(const char * name) const
{
    return gl::GetUniformLocation(handle_, name);
}



bool GLSLProgram::fileExists( const std::string & fileName )
{
    struct stat info;
    JU::int32 ret = -1;

    ret = stat(fileName.c_str(), &info);
    return 0 == ret;
}

} // namespace JU
