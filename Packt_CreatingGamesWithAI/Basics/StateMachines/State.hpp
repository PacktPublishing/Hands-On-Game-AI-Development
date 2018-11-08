//
//  State.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 12/09/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#ifndef State_hpp
#define State_hpp

// State of a state machine
template <class entity_type>
class State
{
public:
    
    virtual ~State() {}
    
    // When we enter to the state
    virtual void onEnter(entity_type*) = 0;
    
    // When it is time to run the update
    virtual void onExecute(entity_type*) = 0;
    
    // When we leave the state
    virtual void onExit(entity_type*) = 0;
};

#endif /* State_hpp */
