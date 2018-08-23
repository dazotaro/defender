/*
 * SDLEventManager.cpp
 *
 *  Created on: Jun 4, 2015
 *      Author: jusabiaga
 */

// Local includes
#include "SDLEventManager.hpp"
#include "Defs.hpp"         // uint32
#include "SystemLog.hpp"    // JU::logMessage
// Global includes
#include <cstdio>           // std::printf

namespace JU
{

/**
 * Attach an event handler to an event name
 *
 * @param handler_name		Event name
 * @param handler_handler	Event handler
 */
void SDLEvent::attachEventHandler(const std::string& handler_name, SDLEventHandler* event_handler)
{
    EventHandlerMap::iterator result = event_handler_map_.find(handler_name);
    if (result != event_handler_map_.end())
    {
        std::stringstream error_stream;
        error_stream << FUNCTION_NAME << "Event handler " << handler_name << "with that name already exists";
        SystemLog::logMessage("SDLEvent", error_stream.str().c_str(), true);
    }
    else
    {
        event_handler_map_[handler_name] = event_handler;
    }
}


/**
 * Detach event handler
 *
 * @param handler_name Handler name
 */
void SDLEvent::detachEventHandler(const std::string& handler_name)
{
    EventHandlerMap::iterator result = event_handler_map_.find(handler_name);
    if (result == event_handler_map_.end())
    {
        std::stringstream error_stream;
        error_stream << FUNCTION_NAME << "Event handler '" << handler_name << "' does not exist";
        SystemLog::logMessage(FUNCTION_NAME, error_stream.str().c_str(), true);
    }
    else
    {
        event_handler_map_.erase(result);
    }
}


/**
 * @brief Handle an event
 *
 * Present an event to all of the event handlers
 *
 * @param event Event to be handled
 */
void SDLEvent::handleEvent(const SDL_Event* event) const
{
    for (EventHandlerMap::const_iterator iter = event_handler_map_.begin(); iter != event_handler_map_.end(); ++iter)
    {
        iter->second->handleSDLEvent(event);
    }
}


/**
* Default Constructor
*
*/
SDLEventManager::SDLEventManager (): quit_(false)
{
}


/**
* Destructor
*
*/
SDLEventManager::~SDLEventManager ()
{
}


/**
* Initialize all components of input
*
* @return True if successful, false otherwise
*/
bool SDLEventManager::initialize()
{
    return true;
}


/**
* @brief Update event queue
*
* Go through all the events available since the last update
*
* @return True if successful, false otherwise
*/
bool SDLEventManager::update()
{
    static uint32 frame_id = 0;
    frame_id++;
    //Event handler
    SDL_Event event;

    //Handle events on queue
    while (SDL_PollEvent( &event ) != 0)
    {
        switch(event.type)
        {
            case SDL_QUIT:
                quit_ = true;
                break;

            case SDL_KEYDOWN:
            case SDL_KEYUP:
            case SDL_MOUSEMOTION:
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
            case SDL_MOUSEWHEEL:
            case SDL_WINDOWEVENT:   // Window size has changed
                {
                    SDLEventHashMap::iterator iter = event_handlers_hashmap_.find(event.type);
                    if (iter == event_handlers_hashmap_.end())
                    {
                        char buffer[100];
                        std::sprintf(buffer, "%s:Event type (%x) has no handler assigned\n", __PRETTY_FUNCTION__, event.type);
                        SystemLog::logMessage(FUNCTION_NAME, buffer, false);
                    }
                    else
                    {
                        iter->second.handleEvent(&event);
                    }
                }
                break;

            default:
                //std::printf ("Unhandled SDL2 event %i\n", event.type);
                break;
        }
    }

    return true;
}


/**
 * Are we quitting the application? e.g. did the 'esc' was pressed?
 */
bool SDLEventManager::quitting() const
{
    return quit_;
}


/**
 * Attach an event handler to an event id
 *
 * @param event_id		Event id
 * @param handler_name	Event handler name
 * @param event_handler	Address of Event handler
 */
void SDLEventManager::attachEventHandler(SDLEvent::EventID event_id, const std::string& handler_name, SDLEventHandler* event_handler)
{
    SDLEventHashMap::iterator result = event_handlers_hashmap_.find(event_id);
    // Is this a new event type?
    if (result == event_handlers_hashmap_.end())
    {
        SDLEvent event (event_id);
        event.attachEventHandler(handler_name, event_handler);
        event_handlers_hashmap_[event_id] = event;
    }
    else
    {
        result->second.attachEventHandler(handler_name, event_handler);
    }
}


/**
 * Detach and event handler
 *
 * @param event_id 		Event id
 * @param handler_name	Event handler name
 */
void SDLEventManager::detachEventHandler(SDLEvent::EventID event_id, const std::string& handler_name)
{
    SDLEventHashMap::iterator result = event_handlers_hashmap_.find(event_id);
    // Is this a new event type?
    if (result == event_handlers_hashmap_.end())
    {
        std::stringstream error_stream;
        error_stream << FUNCTION_NAME << "Handler '" <<  handler_name << "' for event " << event_id << "does not exist";
        SystemLog::logMessage(FUNCTION_NAME, error_stream.str().c_str(), true);
    }
    else
    {
        event_handlers_hashmap_.erase(result);
    }
}


} /* namespace JU */
