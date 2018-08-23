/*
 * Timer.hpp
 *
 *  Created on: Jun 30, 2015
 *      Author: jusabiaga
 */

#ifndef TIMER_HPP_
#define TIMER_HPP_

#include "Defs.hpp"		// JU::uint32

namespace JU
{

/**
 * Timer class
 */
class Timer
{
    public:
        Timer();

        //The various clock actions
        void start();
        void stop();
        void pause();
        void unpause();

        //Gets the timer's time
        uint32 getTicks();

        //Checks the status of the timer
        bool isStarted();
        bool isPaused();

    private:

        uint32 start_ticks_;	//!< The clock time when the timer started
        uint32 paused_ticks_;	//!< The ticks stored when the timer was paused
        bool paused_;			//!< Is paused?
        bool started_;			//!< Has started?
};

} /* namespace JU */

#endif /* TIMER_HPP_ */
