//
//  KeyboardEvents.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 14/12/2017.
//  Copyright © 2017 Cihan Ozer. All rights reserved.
//

#ifndef KeyboardEvents_hpp
#define KeyboardEvents_hpp

#include "Event.hpp"

class KeyboardEvents : public Event
{
public:
    
    enum KEYBOARD_EVENTS{ KEY_DOWN, KEY_UP  };
    
    KeyboardEvents();
    KeyboardEvents(const unsigned int eventType, const SDL_Keycode keyCode);
    
    SDL_Keycode key;
};

#endif /* KeyboardEvents_hpp */
