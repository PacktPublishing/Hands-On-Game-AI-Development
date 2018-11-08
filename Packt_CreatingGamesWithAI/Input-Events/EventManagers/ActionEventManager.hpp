//
//  ActionEventManager.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 16/03/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#ifndef ActionEventManager_hpp
#define ActionEventManager_hpp

#include "Subject.hpp"

// Event manager for SDLinator5000 Action events
class ActionEventManager : public Subject<ActionEvent>
{
public:
    
    ActionEventManager();
    ~ActionEventManager();
};

#endif /* ActionEventManager_hpp */
