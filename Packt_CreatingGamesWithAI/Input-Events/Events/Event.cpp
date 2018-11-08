//
//  Event.cpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 23/12/2017.
//  Copyright © 2017 Cihan Ozer. All rights reserved.
//

#include "Event.hpp"

Event::Event()
{
    
}

Event::Event(const unsigned int parent, const unsigned int eventType)
    : PARENT_EVENT(parent), EVENT_TYPE(eventType)
{
    
}
