/*
 * Keyboard.hpp
 *
 *  Created on: Jun 4, 2015
 *      Author: jusabiaga
 */

#ifndef KEYBOARD_HPP_
#define KEYBOARD_HPP_

// Local includes
#include "SDLEventManager.hpp"  // JU::SDLEventHandler

// Global includes
#include <SDL2/SDL.h>    // SDL_Event


namespace JU
{

	/**
	 * Class to implement a keyboard handler for SDL events
	 */
    class Keyboard : public SDLEventHandler
    {
        enum KeyState
        {
            KEY_DOWN = SDL_PRESSED,
            KEY_UP   = SDL_RELEASED
        };

        public:
            Keyboard();
            void reset();
            bool isKeyUp(SDL_Scancode key) const;
            bool isKeyDown(SDL_Scancode key) const;

#ifdef _DEBUG
            void printKeyboard() const;
#endif

        public:
            void handleSDLEvent(const SDL_Event* event);

        private:
            KeyState keyState_[SDL_NUM_SCANCODES];
    };

} /* namespace JU */

#endif /* KEYBOARD_HPP_ */
