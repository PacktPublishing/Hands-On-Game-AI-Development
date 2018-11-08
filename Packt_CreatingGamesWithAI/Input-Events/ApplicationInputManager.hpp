//
//  ApplicationInputManager.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 14/12/2017.
//  Copyright © 2017 Cihan Ozer. All rights reserved.
//

#ifndef ApplicationInputManager_hpp
#define ApplicationInputManager_hpp

#include "Commons.hpp"

#include "Observer.hpp"

#include "Application.hpp"

#include <vector>

#include <list>
#include <map>
#include <functional>

//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                  //
//  ApplicationInputManager decouple core InputManager from the applications and provide event      //
//  management service for the application, such as games, built using SDLinator5000.               //
//                                                                                                  //
//////////////////////////////////////////////////////////////////////////////////////////////////////

#define AppInputManager ApplicationInputManager::getInstance()

class ApplicationInputManager: public Observer
{
public:
    
    static ApplicationInputManager& getInstance();
    
    void actionEventCallback(ActionEvent pEvent);
    void keyboardEventCallback(KeyboardEvents pEvent);
    void mouseEventCallback(MouseEvents pEvent);
    
    void addSdlinatorCallback( Application* const object, void(Application::* const func)(ActionEvent) );
    void addKeyboardCallback( Application* const object, void(Application::* const func)(KeyboardEvents) );
    void addMouseCallback( Application* const object, void(Application::* const func)(MouseEvents) );
    
    void removeFromAllListeners(const int pCallbackId);
    void removeActionCallback(const int pCallbackId);
    void removeKeyboardCallback(const int pCallbackId);
    void removeMouseCallback(const int pCallbackId);

    void callForSdlinatorEvents(ActionEvent pEvent);
    void callForKeyboardEvents(KeyboardEvents pEvent);
    void callForMouseEvents(MouseEvents pEvent);
    
private:
    
    ApplicationInputManager();
    ~ApplicationInputManager();
    
    std::list<std::function<void(ActionEvent)> > mSdlinatorCallbacks;
    std::map<int, std::list<std::function<void(ActionEvent)> >::iterator> mSdlinatorCbRegister;
    
    std::list<std::function<void(KeyboardEvents)> > mKeyboardCallbacks;
    std::map<int, std::list<std::function<void(KeyboardEvents)> >::iterator> mKeyboardCbRegister;
    
    std::list<std::function<void(MouseEvents)> > mMouseEventCallbackcs;
    std::map<int, std::list<std::function<void(MouseEvents)> >::iterator> mMouseEventCbRegister;
};

#endif /* ApplicationInputManager_hpp */
