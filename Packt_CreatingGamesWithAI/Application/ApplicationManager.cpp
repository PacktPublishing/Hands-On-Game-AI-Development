//
//  ApplicationManager.cpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 06/12/2017.
//  Copyright © 2017 Cihan Ozer. All rights reserved.
//

#include "ApplicationManager.hpp"

#include "InputManager.hpp"
#include "ApplicationInputManager.hpp"
#include "Timer.hpp"

///////////// CONSTRUCTOR - DESTRUCTOR /////////////

ApplicationManager& ApplicationManager::getInstance()
{
    static ApplicationManager instance;
    return instance;
}

ApplicationManager::ApplicationManager()
{
    // TODO Still needs a road-map kinda thing to init and start the
    // related applications.
    
    mApplicationList.reserve(1);
    mNumOfDoneExes = 0;
    
    init();
}

ApplicationManager::~ApplicationManager()
{
    InputMngr.removeFromListeners(  AppInputManager.getId() );
    InputMngr.removeFromListeners( getId() );
    
    mApplicationList.clear();
}

///////////// PUBLIC METHODS /////////////

void ApplicationManager::actionEventCallback(ActionEvent pEvent)
{
    if(pEvent.EVENT_TYPE == ActionEvent::QUIT_EVENT)
    {
        mNumOfDoneExes++;
    }
}

void ApplicationManager::keyboardEventCallback(KeyboardEvents pEvent)
{
    if(pEvent.EVENT_TYPE == KeyboardEvents::KEY_UP && pEvent.key == SDLK_q)
    {
        mNumOfDoneExes++;
    }
}

void ApplicationManager::startExecution()
{
    // The core of the game loop
    
    Time.start();
    
    auto now = std::chrono::steady_clock::now();

    while( mNumOfDoneExes < mApplicationList.size() )
    {
        InputMngr.handleEvents();
        Time.update();
        
        for(int ai = 0; ai < mApplicationList.size(); ++ai)
        {
            mApplicationList[ai]->update();
        }
        
        
        auto res = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - now).count() / 1000000.0f;
        if(res > 1)
        {
            now = std::chrono::steady_clock::now();
        }
        
    }
    
    //Free resources and close SDL
    Time.stop();
    close();
}

///////////// PRIVATE METHODS /////////////

// TODO should not be here...
// Will be gone with the "road map"
#include "TicTacToeGame.hpp"
#include "BattleCityGame.hpp"
#include "PacmanLikeGame.hpp"

bool ApplicationManager::init()
{
    bool isReady = true;
    
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) > -1 )
    {
        InputMngr.addToActionListener(this, &Observer::actionEventCallback);
        InputMngr.addToKeyboardListener(this, &Observer::keyboardEventCallback);

        InputMngr.addToActionListener(&AppInputManager, &Observer::actionEventCallback);
        InputMngr.addToKeyboardListener(&AppInputManager, &Observer::keyboardEventCallback);
        InputMngr.addToMouseListener(&AppInputManager, &Observer::mouseEventCallback);

        // TODO: THIS IS WHERE YOU CURRENTLY CHANGE BETWEEN THE GAMES!
        mApplicationList.emplace_back( std::make_unique<TicTacToeGame>() );
//        mApplicationList.emplace_back(std::make_unique<BattleCityGame>());
//        mApplicationList.emplace_back(std::make_unique<PacmanLikeGame>());
    }
    else
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        isReady = false;
    }
    
    return isReady;
}

bool ApplicationManager::close()
{
    //Quit SDL subsystems
    SDL_Quit();
    
    return true;
}
