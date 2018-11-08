//
//  InputManager.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 07/12/2017.
//  Copyright © 2017 Cihan Ozer. All rights reserved.
//

#ifndef InputManager_hpp
#define InputManager_hpp

#include <SDL2/SDL_events.h>

#include "ActionEventManager.hpp"
#include "KeyboardEventManager.hpp"
#include "MouseEventManager.hpp"

//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                  //
//  InputManager lies between the core system and the applications built on it. InputManager polls  //
//  the event, generates related event object, and notifies the listeners,                          //
//                                                                                                  //
//  Currently, ApplicationManager and ApplicationInputManager register themselves to InputManager   //
//                                                                                                  //
//////////////////////////////////////////////////////////////////////////////////////////////////////

#define InputMngr InputManager::getInstance()

class InputManager
{
public:
    
    static InputManager& getInstance();
    
    void handleEvents();
    
    void addToActionListener(Observer* const object, void(Observer::* const func)(ActionEvent) );
    void addToKeyboardListener(Observer* const object, void(Observer::* const func)(KeyboardEvents) );
    void addToMouseListener(Observer* const object, void(Observer::* const func)(MouseEvents) );
    
    void removeFromListeners(const int pObserverId);
    
private:
    
    InputManager();
    ~InputManager();
    
    SDL_Event mSdlEvent;
    
    ActionEventManager mActionEventManager;
    KeyboardEventManager mKeyboardEventManager;
    MouseEventManager mMouseEventManager;
    
    ActionEvent mActionEvent;
    MouseEvents mMouseEvent;
    KeyboardEvents mKeyboardEvent;
};

#endif /* InputManager_hpp */
