/*
 * SDLEventManager.hpp
 *
 *  Created on: Jun 4, 2015
 *      Author: jusabiaga
 */

#ifndef SDLEVENTMANAGER_HPP_
#define SDLEVENTMANAGER_HPP_

// Local includes
#include "Defs.hpp"			// uint32
// Global includes
#include <unordered_map>    // std::unordered_map
#include <map>				// std::map
#include <SDL2/SDL.h>    // SDL_Event


namespace JU
{
	class SDLEventHandler
	{
		public:
			virtual ~SDLEventHandler() {};

			virtual void handleSDLEvent(const SDL_Event* event) = 0;
	};

	class SDLEvent
	{
		public:
			// Type Definitions
			typedef uint32 EventID;
			typedef std::map<std::string, SDLEventHandler*> EventHandlerMap;

		public:
			SDLEvent(EventID event_id = 0) : event_id_(event_id) {}

			void attachEventHandler(const std::string& handler_name, SDLEventHandler* event_handler);
            void detachEventHandler(const std::string& handler_name);
            void handleEvent(const SDL_Event* event) const;

		public:
			EventID 		event_id_;
			EventHandlerMap event_handler_map_;
	};

    class SDLEventManager
    {
        public:
            SDLEventManager ();
            virtual ~SDLEventManager ();

        public:
            bool initialize();
            bool update();
            bool quitting() const;

            void attachEventHandler(SDLEvent::EventID event_id, const std::string& handler_name, SDLEventHandler* event_handler);
            void detachEventHandler(SDLEvent::EventID event_id, const std::string& handler_name);

        private:
            // Type Definitions
            typedef std::unordered_map<SDLEvent::EventID, SDLEvent> SDLEventHashMap;

        private:
            bool 	 		quit_;
            SDLEventHashMap	event_handlers_hashmap_;
    };

} /* namespace JU */

#endif /* SDLEVENTMANAGER_HPP_ */
