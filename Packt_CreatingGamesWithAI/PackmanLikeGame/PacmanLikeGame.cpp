//
//  PackmanLikeGame.cpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 13/09/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#include "PacmanLikeGame.hpp"

#include "PLG_Commons.hpp"
#include "GameEventManager.hpp"

PacmanLikeGame::PacmanLikeGame()
    : Application()
{
    mIsReadyToRun = init();
    mIsQuit = !mIsReadyToRun;
}

void PacmanLikeGame::reset()
{
    mGameWorld.reset();
}

void PacmanLikeGame::actionEventCallback(ActionEvent pEvent)
{
    if(pEvent.EVENT_TYPE == ActionEvent::QUIT_EVENT)
    {
        mIsQuit = true;
    }
}

void PacmanLikeGame::mouseEventCallback(MouseEvents pEvent)
{
    // Send the mouse event
    GameEventMngr.callForMouseEvents(pEvent);
}

void PacmanLikeGame::keyboardEventCallback(KeyboardEvents pEvent)
{
    if(pEvent.EVENT_TYPE == KeyboardEvents::KEY_UP)
    {
        if(pEvent.key == SDLK_n)
        {
            reset();
            return;
        }
        else if(pEvent.key == SDLK_q)
        {
            mIsQuit = true;
            return;
        }
    }
    
    GameEventMngr.callForKeyboardEvents(pEvent);
}

void PacmanLikeGame::update()
{
    if(mIsQuit)
    {
        mWindow->close();
    }
    else
    {
        mGameWorld.callOnFrame();
        
        mWindow->pushTextures(mGameWorld.getObjectTextures());
        mWindow->callOnFrame();
    }
}

bool PacmanLikeGame::init()
{
    mWindowPosX = SDL_WINDOWPOS_CENTERED;
    mWindowPosY = SDL_WINDOWPOS_CENTERED;
    
    mWindowWidth= WINDOW_WIDTH;
    mWindowHeight = WINDOW_HEIGHT;
    mTitle= "Packman-Like Game";
    
    mWindow = std::make_unique<ApplicationWindow>();
    
    SDL_Color backGroundColor;
    backGroundColor.r = 0x00;
    backGroundColor.g = 0x00;
    backGroundColor.b = 0x00;
    backGroundColor.a = 0x00;
    
    auto result = mWindow->init(mTitle, mWindowPosX, mWindowPosY, mWindowWidth, mWindowHeight, SDL_WINDOW_SHOWN, mImagePath, backGroundColor);
    
    if(result)
    {
        mGameWorld.constructGameWorld();
    }
    return result;
}
