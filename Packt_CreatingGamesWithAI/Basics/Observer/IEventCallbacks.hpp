//
//  IEventCallbacks.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 26/03/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#ifndef IEventCallbacks_hpp
#define IEventCallbacks_hpp

#include "ActionEvent.hpp"
#include "MouseEvents.hpp"
#include "KeyboardEvents.hpp"

//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                  //
//  IEventCallbacks is an interface for the classes that will implement callbacks. SDLinator5000    //
//  currently supports keyboard, mouse, and Action (Events that belong to SDLinator5000 originally  //
//  such as quit event) events.                                                                     //
//                                                                                                  //
//////////////////////////////////////////////////////////////////////////////////////////////////////

class IEventCallbacks
{
public:
    
    virtual ~IEventCallbacks()  {   }
    
    virtual void actionEventCallback(ActionEvent pEvent) = 0;
    virtual void keyboardEventCallback(KeyboardEvents pEvent) = 0;
    virtual void mouseEventCallback(MouseEvents pEvent) = 0;
};

#endif /* IEventCallbacks_hpp */
