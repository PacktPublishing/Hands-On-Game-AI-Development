//
//  GameEventManager.cpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 18/05/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#include "GameEventManager.hpp"


GameEventManager& GameEventManager::getInstance()
{
    static GameEventManager instance;
    return instance;
}

GameEventManager::GameEventManager()
{
    
}

GameEventManager::~GameEventManager()
{
    mSdlinatorCbRegister.clear();
    mKeyboardCbRegister.clear();
    mMouseEventCbRegister.clear();
    
    mSdlinatorCallbacks.clear();
    mKeyboardCallbacks.clear();
    mMouseEventCallbackcs.clear();
}

void GameEventManager::addSdlinatorCallback(Observer *const object, void (Observer::* const func)(ActionEvent))
{
    using namespace std::placeholders;
    
    auto it = mSdlinatorCbRegister.find( object->getId() );
    if(it == mSdlinatorCbRegister.end() )
    {
        mSdlinatorCallbacks.emplace_back( std::bind(func, object, _1) );
        mSdlinatorCbRegister.insert( std::pair<int, std::list<std::function<void(ActionEvent)> >::iterator>(object->getId(), std::prev(mSdlinatorCallbacks.end() ) ) );
    }
}

void GameEventManager::addKeyboardCallback(Observer *const object, void (Observer::* const func)(KeyboardEvents))
{
    using namespace std::placeholders;
    
    auto it = mKeyboardCbRegister.find( object->getId() );
    if(it == mKeyboardCbRegister.end() )
    {
        mKeyboardCallbacks.emplace_back( std::bind(func, object, _1) );
        mKeyboardCbRegister.insert( std::pair<int, std::list<std::function<void(KeyboardEvents)> >::iterator>(object->getId(), std::prev(mKeyboardCallbacks.end() ) ) );
    }
}

void GameEventManager::addMouseCallback(Observer *const object, void (Observer::* const func)(MouseEvents))
{
    using namespace std::placeholders;
    
    auto it = mMouseEventCbRegister.find( object->getId() );
    if(it == mMouseEventCbRegister.end() )
    {
        mMouseEventCallbackcs.emplace_back( std::bind(func, object, _1) );
        mMouseEventCbRegister.insert( std::pair<int, std::list<std::function<void(MouseEvents)> >::iterator>(object->getId(), std::prev(mMouseEventCallbackcs.end() ) ) );
    }
}

void GameEventManager::removeFromAllListeners(const int pCallbackId)
{
    removeActionCallback(pCallbackId);
    removeKeyboardCallback(pCallbackId);
    removeMouseCallback(pCallbackId);
}

void GameEventManager::removeActionCallback(const int pCallbackId)
{
    auto it = mSdlinatorCbRegister.find(pCallbackId);
    if(it != mSdlinatorCbRegister.end() )
    {
        mSdlinatorCallbacks.erase( mSdlinatorCbRegister[pCallbackId] );
        mSdlinatorCbRegister.erase(it);
    }
}

void GameEventManager::removeKeyboardCallback(const int pCallbackId)
{
    auto it = mKeyboardCbRegister.find(pCallbackId);
    if(it != mKeyboardCbRegister.end() )
    {
        mKeyboardCallbacks.erase( mKeyboardCbRegister[pCallbackId] );
        mKeyboardCbRegister.erase(it);
    }
}

void GameEventManager::removeMouseCallback(const int pCallbackId)
{
    auto it = mMouseEventCbRegister.find(pCallbackId);
    if(it != mMouseEventCbRegister.end() )
    {
        mMouseEventCallbackcs.erase( mMouseEventCbRegister[pCallbackId] );
        mMouseEventCbRegister.erase(it);
    }
}

void GameEventManager::callForSdlinatorEvents(const ActionEvent& pEvent)
{
    for(const auto& cb : mSdlinatorCallbacks)
    {
        cb(pEvent);
    }
}

void GameEventManager::callForKeyboardEvents(const KeyboardEvents& pEvent)
{
    for(const auto& cb : mKeyboardCallbacks)
    {
        cb(pEvent);
    }
}

void GameEventManager::callForMouseEvents(const MouseEvents& pEvent)
{
    for(const auto& cb : mMouseEventCallbackcs)
    {
        cb(pEvent);
    }
}
