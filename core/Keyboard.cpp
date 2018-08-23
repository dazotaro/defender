/*
 * Keyboard.cpp
 *
 *  Created on: Jun 4, 2015
 *      Author: jusabiaga
 */

// Local includes
#include "Keyboard.hpp"
#include "Defs.hpp"         // JU::uint32
#include "SystemLog.hpp"    // JU::SystemLog

// Global includes
#include <cstdio>               // std::printf

namespace JU
{
/**
* @brief Default Constructor
*
* Initialize all key states to UP
*
*/
Keyboard::Keyboard()
{
    reset();
}


/**
* @brief Reset Method
*
* Initialize all key states to UP
*
*/
void Keyboard::reset()
{
    // All Keys are up
    for (uint32 index = 0; index < SDL_NUM_SCANCODES; index++)
        keyState_[index] = KEY_UP;
}


/**
* @brief Handle keyboard events
*
* Process and SDL2 keyboard event
*
* @param code The SDL_KeyboardEvent of the key to check (SDL2/SDL_Scancode.h)
*
* @return True if successful
*
*/
void Keyboard::handleSDLEvent(const SDL_Event* event)
{
    switch (event->key.state)
    {
        case SDL_PRESSED:
            keyState_[event->key.keysym.scancode] = KEY_DOWN;
            break;

        case SDL_RELEASED:
            keyState_[event->key.keysym.scancode] = KEY_UP;
            break;

        default:
            SystemLog::logMessage("Keyboard", "handleEvent(): event state not handled", true);
            break;

    }
}


/**
* @brief Is Key Up?
*
* Checks the state of key
*
* @param code The SDL_Scancode of the key to check (SDL2/SDL_Scancode.h)
*
* @return True if the key is up, false otherwise
*
*/
bool Keyboard::isKeyUp(SDL_Scancode code) const
{
    if (keyState_[code] == KEY_UP)
        return true;

    return false;
}


/**
* @brief Is Key Down?
*
* Checks the state of key
*
* @param code The SDL_Scancode of the key to check (SDL2/SDL_Scancode.h)
*
* @return True if the key is down, false otherwise
*
*/
bool Keyboard::isKeyDown(SDL_Scancode code) const
{
    if (keyState_[code] == KEY_DOWN)
        return true;

    return false;
}


#ifdef _DEBUG
/**
 * Print the keyboard state
 */
void Keyboard::printKeyboard() const
{
    for (JU::uint32 scancode = SDL_SCANCODE_UNKNOWN; scancode < SDL_NUM_SCANCODES; ++scancode)
    {
        if (keyState_[scancode] == SDL_PRESSED)
            std::printf("%s ", SDL_GetKeyName(SDL_GetKeyFromScancode((SDL_Scancode)scancode)));
    }
    std::printf("\n");
}
#endif

} /* namespace JU */
