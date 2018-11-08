//
//  MouseEventManager.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 16/03/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#ifndef MouseEventManager_hpp
#define MouseEventManager_hpp

#include "Subject.hpp"

// Event manager for mouse events
class MouseEventManager : public Subject<MouseEvents>
{
public:
    
    MouseEventManager();
    ~MouseEventManager();
};

#endif /* MouseEventManager_hpp */
