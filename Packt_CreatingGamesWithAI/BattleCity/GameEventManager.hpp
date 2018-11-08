//
//  GameEventManager.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 18/05/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#ifndef GameEventManager_hpp
#define GameEventManager_hpp

#include "LegacyGameCharacter.hpp"

#include <list>
#include <map>
#include <functional>


#define GameEventMngr GameEventManager::getInstance()

class GameEventManager
{
public:
    
    static GameEventManager& getInstance();

    void addSdlinatorCallback( Observer* const object, void(Observer::* const func)(ActionEvent) );
    void addKeyboardCallback( Observer* const object, void(Observer::* const func)(KeyboardEvents) );
    void addMouseCallback( Observer* const object, void(Observer::* const func)(MouseEvents) );
    
    void removeFromAllListeners(const int pCallbackId);
    void removeActionCallback(const int pCallbackId);
    void removeKeyboardCallback(const int pCallbackId);
    void removeMouseCallback(const int pCallbackId);
    
    void callForSdlinatorEvents(const ActionEvent& pEvent);
    void callForKeyboardEvents(const KeyboardEvents& pEvent);
    void callForMouseEvents(const MouseEvents& pEvent);
    
private:
    
    GameEventManager();
    ~GameEventManager();
    
    std::list<std::function<void(ActionEvent)> > mSdlinatorCallbacks;
    std::map<int, std::list<std::function<void(ActionEvent)> >::iterator> mSdlinatorCbRegister;
    
    std::list<std::function<void(KeyboardEvents)> > mKeyboardCallbacks;
    std::map<int, std::list<std::function<void(KeyboardEvents)> >::iterator> mKeyboardCbRegister;
    
    std::list<std::function<void(MouseEvents)> > mMouseEventCallbackcs;
    std::map<int, std::list<std::function<void(MouseEvents)> >::iterator> mMouseEventCbRegister;
};

#endif /* GameEventManager_hpp */
