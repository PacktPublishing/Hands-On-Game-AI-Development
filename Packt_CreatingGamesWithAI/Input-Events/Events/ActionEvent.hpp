//
//  ActionEvent.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 23/12/2017.
//  Copyright © 2017 Cihan Ozer. All rights reserved.
//

#ifndef ActionEvent_hpp
#define ActionEvent_hpp

#include "Event.hpp"

// ActionsEvent class contains the events that belong to SDLinator5000 originally such as quit event
class ActionEvent : public Event
{
    
public:
    
    enum ACTION_EVENTS{ QUIT_EVENT};
    
    ActionEvent();
    ActionEvent(const unsigned int eventType);
};

#endif /* ActionEvent_hpp */
