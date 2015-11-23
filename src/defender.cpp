// Local includes
#include "../graphics/gl_core_4_2.hpp"			// glLoadGen generated header files (need to be included before 'SDL_oepngl.h')
#include "../graphics/GLSLProgramHelper.hpp"	// GLSLProgramHelper
#include "../graphics/GLSLProgram.hpp"			// GLSLProgram
#include "../graphics/GLMesh2D.hpp"				// GLMesh2D
#include "../graphics/GLMesh2DInstance.hpp"		// GLMesh2DInstance
#include "../graphics/Camera2D.hpp"				// Camera2D
#include "../core/SDLEventManager.hpp"		    // JU::SDLEventManager
#include "../core/Singleton.hpp"			    // JU::Singleton
#include "../graphics/TextureManager.hpp"       // JU::TextureManager
#include "../core/Keyboard.hpp"				    // JU::Keyboard
#include "SpriteObject.hpp"                     // JU::SpriteObject
#include "SpaceShip.hpp"			            // JU::SpaceShip
#include "Background.hpp"                       // JU::Background
#include "DynamicGrid.hpp"                      // JU::DynamicGrid
#include "ParticleSystem.hpp"                   // JU::ParticleSystem
#include "../core/Timer.hpp"				    // JU::Timer
#include "../physics/PhysicsEngine.hpp"	        // PhysicsEngine
// Global includes
#include <cstdio>					            // printf
#include <SDL.h>					            // all SDL2
#include <SDL_opengl.h>
#include <map>						            // std::map
#include <string>					            // std::string

namespace
{
// CONSTANTS
const JU::uint32 WIDTH = 1000;                            // Main viewport
const JU::uint32 HEIGHT = 600;                            // Main viewport
const JU::uint32 MINI_WIDTH  = 600;                       // Mini viewport
const JU::uint32 MINI_HEIGHT = 100;                       // Mini viewport
const JU::uint32 GRIDX = 60;
const JU::uint32 GRIDY = 60;
const JU::uint32 MAX_PARTICLES = 50;

// GLOBAL VARIABLES
std::map<std::string, JU::GLSLProgram> g_shader_map;
std::map<std::string, JU::GameObject*> g_game_object_map;
JU::Camera2D* g_pcamera;                                    // Main camera
JU::Camera2D* g_pminicamera;                                // Mini-viewport's camera
JU::SDLEventManager* g_SDL_event_manager;
JU::Keyboard* g_keyboard;
SDL_Window* g_mainwindow; /* Our window handle */
JU::PhysicsEngine* g_physics_engine;
JU::DynamicGrid<GRIDX, GRIDY>* g_pgrid;
JU::ParticleSystem<MAX_PARTICLES>* g_particle_system;
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
    g_SDL_event_manager->attachEventHandler(SDL_KEYUP, "Keyup", g_keyboard);

    // OPENGL
    // -------------
    // Enable blending
    gl::Enable(gl::BLEND);
    gl::BlendFunc(gl::SRC_ALPHA, gl::ONE_MINUS_SRC_ALPHA);// Clear Buffer


    // GLSL PROGRAMS
    // -------------
    g_shader_map["grid"]    = JU::GLSLProgramHelper::compileAndLinkShader("data/shaders/dynamic_grid.vs", "data/shaders/simple.fs");
    g_shader_map["texture"] = JU::GLSLProgramHelper::compileAndLinkShader("data/shaders/texture.vs", "data/shaders/texture.fs");
    g_shader_map["points"]  = JU::GLSLProgramHelper::compileAndLinkShader("data/shaders/point.vs", "data/shaders/point.fs");

    // GameObjects
    // -----------
    g_physics_engine = JU::Singleton<JU::PhysicsEngine>::getInstance();

    JU::SpriteObject* psprite = nullptr;

    psprite = new JU::SpriteObject("enemy1", "data/textures/enemy.png", true);
    psprite->setMoveable2D(JU::Moveable2D(-2.0f, -2.0f, 0.0f, 1.3f, 1.3f));
    g_game_object_map[psprite->getName()] = psprite;
    g_physics_engine->addRigidBody(psprite->getName(),  g_game_object_map[psprite->getName()]->getRigidBody());

    psprite = new JU::SpriteObject("enemy2", "data/textures/enemy.png", true);
    psprite->setMoveable2D(JU::Moveable2D(2.0f, -2.0f, 0.0f, 1.3f, 1.3f));
    g_game_object_map[psprite->getName()] = psprite;
    g_physics_engine->addRigidBody(psprite->getName(),  g_game_object_map[psprite->getName()]->getRigidBody());

    psprite = new JU::SpriteObject("enemy3", "data/textures/enemy.png", true);
    psprite->setMoveable2D(JU::Moveable2D(2.0f, 2.0f, 0.0f, 1.3f, 1.3f));
    g_game_object_map[psprite->getName()] = psprite;
    g_physics_engine->addRigidBody(psprite->getName(),  g_game_object_map[psprite->getName()]->getRigidBody());

    psprite = new JU::SpriteObject("enemy4", "data/textures/enemy.png", true);
    psprite->setMoveable2D(JU::Moveable2D(-2.0f, 2.0f, 0.0f, 1.3f, 1.3f));
    g_game_object_map[psprite->getName()] = psprite;
    g_physics_engine->addRigidBody(psprite->getName(),  g_game_object_map[psprite->getName()]->getRigidBody());

    /*
    psprite = new JU::SpriteObject("background", "data/textures/background.jpg",false);
    psprite->setMoveable2D(JU::Moveable2D(0.0f, 0.0f, 0.0f, 80.0f, 80.0f * HEIGHT / WIDTH));
    g_game_object_map[psprite->getName()] = psprite;
    */

    JU::SpaceShip* pspaceship = new JU::SpaceShip("spaceship", "data/textures/spaceship.png", true);
    pspaceship->setMoveable2D(JU::Moveable2D(0.0f, 0.0f, 0.0f, 1.3f, 1.3f));
    g_game_object_map[pspaceship->getName()] = pspaceship;
    g_physics_engine->addRigidBody(pspaceship->getName(),  g_game_object_map[pspaceship->getName()]->getRigidBody());

    // PARTICLE SYSTEMS
    // ----------------
    // Dynamic Grid
    g_pgrid = new JU::DynamicGrid<GRIDX, GRIDY>(JU::Moveable2D(0.0f, 0.0f, 0.0f, 30.0f, 30.0f),
                                          1.0f, 1.8f, 1.6f, glm::vec4(0.0f, 0.5f, 0.5f, 1.0f));
    // Point-based Particle System
    g_particle_system = new JU::ParticleSystem<MAX_PARTICLES>;
    g_particle_system->init();

    // PHYSICS ENGINE
    // --------------
    g_physics_engine->init();

    // Camera2D
    // --------
    g_pcamera     = new JU::Camera2D(JU::Moveable2D(0.0f, 0.0f, 0.0f, 10.0f, 10.0f * HEIGHT / WIDTH));
    g_pminicamera = new JU::Camera2D(JU::Moveable2D(0.0f, 0.0f, 0.0f, 20.0f, 20.0f * MINI_HEIGHT / MINI_WIDTH));

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
    static JU::Timer timer;
    static JU::uint32 milliseconds = timer.getTicks();

    while (running)
    {
        // EVENT HANDLING
        // --------------
        // sdl events
        g_SDL_event_manager->update();
        if (g_SDL_event_manager->quitting()
                || g_keyboard->isKeyDown(SDL_SCANCODE_ESCAPE))
        {
            running = false;
            break;
        }

        milliseconds = timer.getTicks();
        timer.start();
        std::printf("milliseconds = %i\n", milliseconds);

        // CAMERA
        // -----------
        g_pcamera->getMoveable().position_ = g_game_object_map["spaceship"]->getMoveable().position_;

        // PARTICLE SYSTEM UPDATE
        // ----------------------
        // GRID
        // ----
        glm::vec2 force_positions[] = {g_game_object_map["spaceship"]->getMoveable().position_};
        g_pgrid->update(milliseconds, force_positions, 1);
        // POINT-PARTICLES
        // ---------------
        g_particle_system->addParticle(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 0.0f), 1.0f, 1.0f, 1000);
        g_particle_system->update(milliseconds);

        // GAME OBJECT UPDATE
        // ------------------
        g_game_object_map["spaceship"]->update(milliseconds);
        g_game_object_map["enemy1"]->update(milliseconds);
        g_game_object_map["enemy2"]->update(milliseconds);
        g_game_object_map["enemy3"]->update(milliseconds);
        g_game_object_map["enemy4"]->update(milliseconds);



        //////////////
        // REMOVE IT!!!
        //////////////
        //SDL_Delay(10);
        //////////////
        //////////////

        // COLLISIONS
        // -----------
        g_physics_engine->updateCollisions(milliseconds);

        // RENDER
        // ------
        // Main VIEWPORT
        // *********************************************
        gl::Viewport(0, 0, WIDTH, HEIGHT);
        gl::ClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        gl::Clear(gl::COLOR_BUFFER_BIT);

        // Model is identity
        glm::mat3 model;

        // Get World to Camera matrix
        glm::mat3 view;
        g_pcamera->getWorld2NDCTransformation(view);

        // Grid particle system
        p_program = &g_shader_map["grid"];
        p_program->use();
        g_pgrid->render(*p_program, model, view);

        // Point-particle system
        p_program = &g_shader_map["points"];
        p_program->use();
        g_particle_system->render(*p_program, model, view);

        // All other Sprites
        p_program = &g_shader_map["texture"];
        p_program->use();

        //g_game_object_map["background"]->render(*p_program, model, view);
        g_game_object_map["enemy1"]->render(*p_program, model, view);
        g_game_object_map["enemy2"]->render(*p_program, model, view);
        g_game_object_map["enemy3"]->render(*p_program, model, view);
        g_game_object_map["enemy4"]->render(*p_program, model, view);
        g_game_object_map["spaceship"]->render(*p_program, model, view);

        JU::Singleton<JU::TextureManager>::getInstance()->unbindAllTextures();

        // Mini (overview) VIEWPORT
        // *********************************************
        gl::Viewport((WIDTH - MINI_WIDTH)/2, (HEIGHT - MINI_HEIGHT), MINI_WIDTH, MINI_HEIGHT);

        g_pminicamera->getWorld2NDCTransformation(view);

        // Render all renderables
        g_game_object_map["enemy1"]->render(*p_program, model, view);
        g_game_object_map["enemy2"]->render(*p_program, model, view);
        g_game_object_map["enemy3"]->render(*p_program, model, view);
        g_game_object_map["enemy4"]->render(*p_program, model, view);
        g_game_object_map["spaceship"]->render(*p_program, model, view);

        JU::Singleton<JU::TextureManager>::getInstance()->unbindAllTextures();

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
    for (auto iter = g_game_object_map.begin(); iter != g_game_object_map.end(); iter++)
    {
        delete iter->second;
    }

    delete g_pgrid;

    delete g_pcamera;
    delete g_pminicamera;

    delete g_SDL_event_manager;
    delete g_keyboard;
}


/* Our program's entry point */
int main(int argc, char *argv[])
{
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
    if (!loaded)
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
    SDL_GLContext maincontext = SDL_GL_CreateContext(g_mainwindow);
    checkSDLError(__LINE__);

    /* This makes our buffer swap syncronized with the monitor's vertical refresh */
    SDL_GL_SetSwapInterval(1);

    init();
    loop();
    exit();

    /* Delete our opengl context, destroy our window, and shutdown SDL */
    SDL_GL_DeleteContext(maincontext);
    SDL_DestroyWindow(g_mainwindow);
    SDL_Quit();

    return 0;
}

