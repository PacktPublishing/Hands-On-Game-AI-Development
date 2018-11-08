//
//  KeyboardEvents.cpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 14/12/2017.
//  Copyright © 2017 Cihan Ozer. All rights reserved.
//

#include "KeyboardEvents.hpp"

KeyboardEvents::KeyboardEvents()
    : Event()
{
    
}

KeyboardEvents::KeyboardEvents(const unsigned int eventType, const SDL_Keycode keyCode)
:   Event(SDLINATOR_EVENTS::KEYBOARD_EVENT, eventType),
    key(keyCode)
{
    
}
