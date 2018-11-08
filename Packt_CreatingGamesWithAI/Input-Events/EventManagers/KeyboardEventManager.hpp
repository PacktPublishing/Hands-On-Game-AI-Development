//
//  KeyboardEventManager.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 16/03/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#ifndef KeyboardEventManager_hpp
#define KeyboardEventManager_hpp

#include "Subject.hpp"

// Event manager for keyboard events
class KeyboardEventManager : public Subject<KeyboardEvents>
{
public:
    
    KeyboardEventManager();
    ~KeyboardEventManager();
};

#endif /* KeyboardEventManager_hpp */
