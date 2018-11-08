//
//  BattleCityGame.cpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 25/02/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#include "BattleCityGame.hpp"

#include "BattleCityCommons.hpp"

// TODO Add your own way to tell SDL
#include <SDL2/SDL.h>   // For SDL_WINDOWPOS_CENTERED

#include "GameEventManager.hpp"

///////////// CONSTRUCTOR - DESTRUCTOR /////////////

BattleCityGame::BattleCityGame()
    :   Application()
{
    mIsReadyToRun = init();
    
    mIsQuit = !mIsReadyToRun;
}

BattleCityGame::~BattleCityGame()
{
    
}

///////////// PUBLIC METHODS /////////////

void BattleCityGame::reset()
{

}

void BattleCityGame::actionEventCallback(ActionEvent pEvent)
{
    if(pEvent.EVENT_TYPE == ActionEvent::QUIT_EVENT)
    {
        mIsQuit = true;
    }
}

void BattleCityGame::keyboardEventCallback(KeyboardEvents pEvent)
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

void BattleCityGame::update()
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

///////////// PROTECTED METHODS /////////////

bool BattleCityGame::init()
{
    mWindowPosX = SDL_WINDOWPOS_CENTERED;
    mWindowPosY = SDL_WINDOWPOS_CENTERED;
    
    mWindowWidth= WINDOW_WIDTH;
    mWindowHeight = WINDOW_HEIGHT;
    mTitle= "BattleCity";

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
