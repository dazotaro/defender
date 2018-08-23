/*
 * Timer.cpp
 *
 *  Created on: Jun 30, 2015
 *      Author: jusabiaga
 */

// Local include
#include "Timer.hpp"
// Global include
#include <SDL2/SDL.h>

namespace JU
{

/**
 * Default constructor
 */
Timer::Timer() :
        start_ticks_(0), paused_ticks_(0), paused_(false), started_(false)
{}


/**
 * Start timer
 */
void Timer::start()
{
    //Start the timer
    started_ = true;

    //Unpause the timer
    paused_ = false;

    //Get the current clock time
    start_ticks_ = SDL_GetTicks();
    paused_ticks_ = 0;
}


/**
 * Stop timer
 */
void Timer::stop()
{
    //Stop the timer
    started_ = false;

    //Unpause the timer
    paused_ = false;

    //Clear tick variables
    start_ticks_ = 0;
    paused_ticks_ = 0;
}


/**
 * Pause timer
 */
void Timer::pause()
{
    //If the timer is running and isn't already paused
    if (started_ && !paused_)
    {
        //Pause the timer
        paused_ = true;

        //Calculate the paused ticks
        paused_ticks_ = SDL_GetTicks() - start_ticks_;
        start_ticks_ = 0;
    }
}


/**
 * Resume timer
 */
void Timer::unpause()
{
    //If the timer is running and paused
    if (started_ && paused_)
    {
        //Unpause the timer
        paused_ = false;

        //Reset the starting ticks
        start_ticks_ = SDL_GetTicks() - paused_ticks_;

        //Reset the paused ticks
        paused_ticks_ = 0;
    }
}


/**
 * Get number of ticks since start
 */
uint32 Timer::getTicks()
{
    //The actual timer time
    uint32 time = 0;

    //If the timer is running
    if (started_)
    {
        //If the timer is paused
        if (paused_)
        {
            //Return the number of ticks when the timer was paused
            time = paused_ticks_;
        }
        else
        {
            //Return the current time minus the start time
            time = SDL_GetTicks() - start_ticks_;
        }
    }

    return time;
}


/**
 * Is running?
 *
 * @return True if running, false otherwise
 */
bool Timer::isStarted()
{
    //Timer is running and paused or unpaused
    return started_;
}


/**
 * Is paused?
 *
 * @return True if paused, false otherwise
 */
bool Timer::isPaused()
{
    //Timer is running and paused
    return paused_ && started_;
}

} /* namespace JU */
