// Local incluces
#include "gl_core_4_2.hpp"			// glLoadGen generated header files (need to be included before 'SDL_oepngl.h')
#include "GLSLProgramHelper.hpp"	// GLSLProgramHelper
#include "GLSLProgram.hpp"			// GLSLProgram
#include "GLMesh2D.hpp"				// GLMesh2D
#include "GLMesh2DInstance.hpp"		// GLMesh2DInstance
#include "Camera2D.hpp"				// Camera2D
#include "SDLEventManager.hpp"		// JU::SDLEventManager
#include "Singleton.hpp"			// JU::Singleton
#include "Keyboard.hpp"				// JU::Keyboard
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
	const unsigned int HEIGHT = 800;
	// Global variables
	std::map<std::string, JU::GLSLProgram> 			g_shader_map_;
	std::map<std::string, JU::GLMesh2D*>    		g_glmesh_map_;
	std::map<std::string, JU::GLMesh2DInstance*>    g_glmesh_instance_map_;
	JU::Camera2D* 		 g_pcamera;
	JU::SDLEventManager* g_SDL_event_manager;
	JU::Keyboard*		 g_keyboard;
	SDL_Window*	  g_mainwindow; /* Our window handle */
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
	// KEYBOARD
	// --------
	g_keyboard = JU::Singleton<JU::Keyboard>::getInstance();
	g_keyboard->reset();

	// SDL EVENT MANAGER
	// -----------------
	g_SDL_event_manager = JU::Singleton<JU::SDLEventManager>::getInstance();
	if (!g_SDL_event_manager->initialize())
	{
		std::printf("Input Manager failed to initialize!!!\n");
		exit(0);
	}
	// Register window resize event
	//g_SDL_event_manager->attachEventHandler(SDL_WINDOWEVENT, "MainWindowResize", &window_);

	// KEYBOARD
	// --------
	// Register window resize event
	g_SDL_event_manager->attachEventHandler(SDL_KEYDOWN, "Keydown", g_keyboard);
	g_SDL_event_manager->attachEventHandler(SDL_KEYUP, 	"Keyup",   g_keyboard);

	// GLSL PROGRAMS
    // -------------
    g_shader_map_["simple"]  = JU::GLSLProgramHelper::compileAndLinkShader("data/shaders/simple.vs", "data/shaders/simple.fs");

    // GLMesh2D
    // -------------
    JU::GLMesh2D* p_glmesh = new JU::GLMesh2D();
    p_glmesh->init();
    g_glmesh_map_["quad"] = p_glmesh;

    // Camera2D
    // --------
    g_pcamera = new JU::Camera2D(JU::Moveable2D(0.0f, 0.0f, 0.0f), 10.0f, 10.0f);

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
	bool running = true;
	static JU::GLSLProgram* p_program;

	while (running)
	{
		// SDL EVENTS
		g_SDL_event_manager->update();
		if (g_SDL_event_manager->quitting())
		{
			running = false;
			break;
		}

		gl::ClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		gl::Clear(gl::COLOR_BUFFER_BIT);

		// Bind the GLSL program and this object's VAO
		p_program = &g_shader_map_["simple"];
		p_program->use();

		// Get World to Camera matrix
		glm::mat3 view;
		g_pcamera->getWorld2NDCTransformation(view);

		std::map<std::string, JU::GLMesh2DInstance*>::const_iterator iter;
		for (iter = g_glmesh_instance_map_.begin(); iter != g_glmesh_instance_map_.end(); ++iter)
			iter->second->render(*p_program, glm::mat3(), view);

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

	delete g_pcamera;

	delete g_SDL_event_manager;
	delete g_keyboard;
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

    init();
    loop();
    exit();

    /* Delete our opengl context, destroy our window, and shutdown SDL */
    SDL_GL_DeleteContext(maincontext);
    SDL_DestroyWindow(g_mainwindow);
    SDL_Quit();

    return 0;
}

