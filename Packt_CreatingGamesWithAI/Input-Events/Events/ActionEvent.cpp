//
//  ActionEvent.cpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 23/12/2017.
//  Copyright © 2017 Cihan Ozer. All rights reserved.
//

#include "ActionEvent.hpp"

ActionEvent::ActionEvent()
: Event()
{
    
}

ActionEvent::ActionEvent(const unsigned int eventType)
:   Event(SDLINATOR_EVENTS::ACTION_EVENT, eventType)
{
    
}
