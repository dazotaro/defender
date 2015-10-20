// Local incluces
#include "gl_core_4_2.hpp"			// glLoadGen generated header files (need to be included before 'SDL_oepngl.h')
#include "GLSLProgramHelper.hpp"	// GLSLProgramHelper
#include "GLSLProgram.hpp"			// GLSLProgram
#include "GLMesh2D.hpp"				// GLMesh2D
#include "GLMesh2DInstance.hpp"		// GLMesh2DInstance
// Global includes
#include <cstdio>					// printf
#include <SDL.h>					// all SDL2
#include <SDL_opengl.h>
#include <map>						// std::map
#include <string>					// std::string

namespace
{
	// CONSTANTS
	const unsigned int WIDTH = 800;
	const unsigned int HEIGHT = 600;
	// Global variables
	std::map<std::string, JU::GLSLProgram> 			g_shader_map_;
	std::map<std::string, JU::GLMesh2D*>    		g_glmesh_map_;
	std::map<std::string, JU::GLMesh2DInstance*>    g_glmesh_instance_map_;
	SDL_Window*								g_mainwindow; /* Our window handle */
}


/* A simple function that prints a message, the error code returned by SDL,
 * and quits the application */
void sdldie(const char *msg)
{
    std::printf("%s: %s\n", msg, SDL_GetError());
    SDL_Quit();
    exit(1);
}


void checkSDLError(int line = -1)
{
#ifndef NDEBUG
	const char *error = SDL_GetError();
	if (*error != '\0')
	{
		std::printf("SDL Error: %s\n", error);
		if (line != -1)
			std::printf(" + line: %i\n", line);
		SDL_ClearError();
	}
#endif
}


/**
* @brief Initialization function
*
* @detail Initialize application
*/
void init()
{
    // GLSL PROGRAMS
    // -------------
    g_shader_map_["simple"]  = JU::GLSLProgramHelper::compileAndLinkShader("data/shaders/simple.vs", "data/shaders/simple.fs");

    // GLMesh2D
    // -------------
    JU::GLMesh2D* p_glmesh = new JU::GLMesh2D();
    p_glmesh->init();
    g_glmesh_map_["quad"] = p_glmesh;
    // GLMesh2DInstance
    // -------------
    JU::GLMesh2DInstance* p_glmesh_instance = new JU::GLMesh2DInstance(p_glmesh, glm::vec2(1.0f, 1.0f));
    g_glmesh_instance_map_["sprite"] = p_glmesh_instance;
}


/**
* @brief Game loop
*
* @detail Infinite game loop
*/
void loop()
{
	static JU::GLSLProgram* p_program;

	unsigned counter = 10000;
	while (counter--)
	{
		gl::ClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		gl::Clear(gl::COLOR_BUFFER_BIT);

		// Bind the GLSL program and this object's VAO
		p_program = &g_shader_map_["simple"];
		p_program->use();

		std::map<std::string, JU::GLMesh2DInstance*>::const_iterator iter;
		for (iter = g_glmesh_instance_map_.begin(); iter != g_glmesh_instance_map_.end(); ++iter)
			iter->second->render(*p_program, glm::mat3(), glm::mat3());

	    /* Swap our back buffer to the front */
	    SDL_GL_SwapWindow(g_mainwindow);

	    // Unbind GLSL Program
		gl::UseProgram(0);
	}
}


/**
* @brief Exit function
*
* @detail Clean up before termination
*/
void exit()
{
	std::map<std::string, JU::GLMesh2D*>::const_iterator iter_mesh;
	for (iter_mesh = g_glmesh_map_.begin(); iter_mesh != g_glmesh_map_.end(); ++iter_mesh)
		delete iter_mesh->second;

	std::map<std::string, JU::GLMesh2DInstance*>::const_iterator iter_instance;
	for (iter_instance = g_glmesh_instance_map_.begin(); iter_instance != g_glmesh_instance_map_.end(); ++iter_instance)
		delete iter_instance->second;
}


/* Our program's entry point */
int main(int argc, char *argv[])
{
    SDL_GLContext maincontext; /* Our opengl context handle */

    if (SDL_Init(SDL_INIT_VIDEO) < 0) /* Initialize SDL's Video subsystem */
        sdldie("Unable to initialize SDL"); /* Or die on error */

    /* Request opengl 3.2 context.
     * SDL doesn't have the ability to choose which profile at this time of writing,
     * but it should default to the core profile */
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

    /* Turn on double buffering with a 24bit Z buffer.
     * You may need to change this to 16 or 32 for your system */
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    //------------------------------------
    // glLoadGen required initialization
	gl::exts::LoadTest loaded = gl::sys::LoadFunctions();
	if(!loaded)
	{
		//Destroy the context and abort
		return 0;
	}

    //int num_failed = loaded - gl::sys::LOAD_SUCCEEDED;
    //std::printf("Number of functions that failed to load: %i.\n",num_failed);
    //------------------------------------

    /* Create our window centered at 512x512 resolution */
    g_mainwindow = SDL_CreateWindow("Defender", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WIDTH, HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (!g_mainwindow) /* Die if creation failed */
        sdldie("Unable to create window");

    checkSDLError(__LINE__);

    /* Create our opengl context and attach it to our window */
    maincontext = SDL_GL_CreateContext(g_mainwindow);
    checkSDLError(__LINE__);


    /* This makes our buffer swap syncronized with the monitor's vertical refresh */
    SDL_GL_SetSwapInterval(0);

    /* Clear our buffer with a red background */
    gl::ClearColor ( 1.0, 0.0, 0.0, 1.0 );
    gl::Clear ( gl::COLOR_BUFFER_BIT );
    /* Swap our back buffer to the front */
    SDL_GL_SwapWindow(g_mainwindow);
    /* Wait 2 seconds */
    SDL_Delay(2000);

    init();
    loop();
    exit();

    /* Delete our opengl context, destroy our window, and shutdown SDL */
    SDL_GL_DeleteContext(maincontext);
    SDL_DestroyWindow(g_mainwindow);
    SDL_Quit();

    return 0;
}

