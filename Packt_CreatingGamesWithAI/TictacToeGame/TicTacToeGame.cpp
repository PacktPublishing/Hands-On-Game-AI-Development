//
//  TicTacToeGame.cpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 06/12/2017.
//  Copyright © 2017 Cihan Ozer. All rights reserved.
//

#include "TicTacToeGame.hpp"

//#include "ApplicationInputManager.hpp"

// TODO Add your own way to tell SDL
#include <SDL2/SDL.h>   // For SDL_WINDOWPOS_CENTERED

///////////// CONSTRUCTOR - DESTRUCTOR /////////////

TicTacToeGame::TicTacToeGame()
    : Application()
{
    mIsReadyToRun = init();
    
    mIsQuit = !mIsReadyToRun;
}

TicTacToeGame::~TicTacToeGame()
{
    mGameTextures.clear();
}

///////////// PUBLIC METHODS /////////////

void TicTacToeGame::reset()
{
    mTurn = (int)eMOVE_TURN::eMT_PLAYER;
    mGameState = eGAME_STATES::eGS_GAME;
    
    mWindow->reset();
    
    mGameModel->reset();
    
    mGameTextures.clear();
}

void TicTacToeGame::actionEventCallback(ActionEvent pEvent)
{
    if(pEvent.EVENT_TYPE == ActionEvent::QUIT_EVENT)
    {
        mIsQuit = true;
    }
}

void TicTacToeGame::keyboardEventCallback(KeyboardEvents pEvent)
{
    if(pEvent.EVENT_TYPE == KeyboardEvents::KEY_UP)
    {
        if(pEvent.key == SDLK_n)
        {
            reset();
        }
        else if(pEvent.key == SDLK_q)
        {
            mIsQuit = true;
        }
    }
}

void TicTacToeGame::mouseEventCallback(MouseEvents pEvent)
{
    if(pEvent.EVENT_TYPE == MouseEvents::MOUSE_UP)
    {
        if(mGameState == eGAME_STATES::eGS_GAME && getTurn() == eMOVE_TURN::eMT_PLAYER)
        {
            evaluatePlayerTurn(pEvent.mousePosX, pEvent.mousePosY);
        }
    }
}

void TicTacToeGame::update()
{
    if(mIsQuit)
    {
        mWindow->close();
    }
    else
    {
        handleGameState();
        
        std::vector<Texture*> textures;
        for(const auto& uPtrTexture : mGameTextures)
        {
            textures.push_back(uPtrTexture.get());
        }
        
        textures.push_back(mGameObjects[0]->getTexture());
        
        mWindow->pushTextures(textures);
        mWindow->callOnFrame();
    }
}

///////////// PROTECTED METHODS /////////////

bool TicTacToeGame::init()
{
    // TODO Add your own way to tell SDL
    mWindowPosX = SDL_WINDOWPOS_CENTERED;
    mWindowPosY = SDL_WINDOWPOS_CENTERED;
    
    mWindowWidth = 500;
    mWindowHeight = 500;
    
    mTitle = "Tic-tac-toe";
    mFieldImagePath = "Images/TicTacToe/area.png";

    mImagePath = "Images/TicTacToe/area.png";
    
    mPlayerImagePath = "Images/TicTacToe/X.png";
    mAiImagePath = "Images/TicTacToe/O.png";
    
    mWindow = std::make_unique<ApplicationWindow>();
    
    SDL_Color backGroundColor;
    backGroundColor.r = 0xFF;
    backGroundColor.g = 0xFF;
    backGroundColor.b = 0xFF;
    backGroundColor.a = 0xFF;
    
    // TODO add some default values for windows.init()
    bool result = mWindow->init(mTitle, mWindowPosX, mWindowPosY, mWindowWidth, mWindowHeight, SDL_WINDOW_SHOWN, mImagePath, backGroundColor);

    if(result)
    {
        int rowColNum = 3;
        mGameModel = std::make_unique<TicTacToeGameModel>(mWindowWidth / rowColNum, rowColNum);
        
        mTurn = (int)eMOVE_TURN::eMT_PLAYER;
        mGameState = eGAME_STATES::eGS_GAME;

        mGameObjects.push_back( std::make_unique<VisualObject>(-1, mFieldImagePath) );
    }
    
    return result;
}

///////////// PRIVATE METHODS /////////////

TicTacToeGame::eMOVE_TURN TicTacToeGame::getTurn()
{
    return (eMOVE_TURN)mTurn;
}

void TicTacToeGame::updateTurn()
{
    mTurn = mTurn + 1;
    if(mTurn >= eMOVE_TURN::eMT_count)
    {
        mTurn = (int)eMOVE_TURN::eMT_PLAYER;
    }
}

void TicTacToeGame::handleGameState()
{
    if(mGameState == eGAME_STATES::eGS_GAME)
    {
        evaluateTurn();
    }
    else
    {
        if(mGameState == eGAME_STATES::eGS_GAMEOVER)
        {
            // TODO Handle if needed
        }
        else
        {
            if(mGameState == eGAME_STATES::eGS_DRAW)
            {
                makeGameOver("Images/TicTacToe/draw.png");
            }
            else if(mGameState == eGAME_STATES::eGS_AI_WIN)
            {
                makeGameOver("Images/TicTacToe/aiWins.png");
            }
            else if(mGameState == eGAME_STATES::eGS_PLAYER_WIN)
            {
                makeGameOver("Images/TicTacToe/playerWins.png");
            }
            
        }   // END OF ELSE NOT GAMEOVER STATE
        
    }   // END OF ELSE NOT GAME STATE
}

void TicTacToeGame::makeGameOver(const std::string &pGameOverImagePath)
{
    mGameTextures.push_back( std::make_unique<Texture>(0, (mWindowHeight / 5) * 2, 2, pGameOverImagePath) );
    mGameState = eGAME_STATES::eGS_GAMEOVER;
}

void TicTacToeGame::checkEndOfGameCase(const eGAME_WINNER pResult)
{
    switch (pResult)
    {
        case eGAME_WINNER::eGW_DRAW:
            mGameState = eGAME_STATES::eGS_DRAW;
            break;
            
        case eGAME_WINNER::eGW_PLAYER:
            mGameState = eGAME_STATES::eGS_PLAYER_WIN;
            break;
            
        case eGAME_WINNER::eGW_AI:
            mGameState = eGAME_STATES::eGS_AI_WIN;
            break;
        case eGAME_WINNER::eGW_CONTINUE:
            mGameState = eGAME_STATES::eGS_GAME;
            break;
    }
}

void TicTacToeGame::evaluateTurn()
{
    if(getTurn() == eMOVE_TURN::eMT_PLAYER_WIN_CHECK)
    {
        checkEndOfGameCase( mGameModel->checkPlayerWinCase() );
        updateTurn();
    }
    else if(getTurn() == eMOVE_TURN::eMT_AI)
    {
        evaluateAiTurn();
        updateTurn();
        
        checkEndOfGameCase( mGameModel->checkAiWinCase() );
        updateTurn();
    }
}

void TicTacToeGame::evaluatePlayerTurn(const int pMouseX, const int pMouseY)
{
    glm::ivec2 rowCol;
    if( mGameModel->handlePlayerMove(pMouseX, pMouseY, rowCol) )
    {
        // Add player's image to the game field
        mGameTextures.push_back( std::make_unique<Texture>(rowCol.y * ( mWindowWidth / 3 ) + 18, rowCol.x * (mWindowHeight / 3) + 15, mPlayerImagePath) );
        
        updateTurn();
    }
}

void TicTacToeGame::evaluateAiTurn()
{
    glm::ivec2 rowCol;
    if( mGameModel->handleAiMove(rowCol) )
    {
        // Add player's image to the game field
        mGameTextures.push_back( std::make_unique<Texture>(rowCol.y * ( mWindowWidth / 3 ) + 18, rowCol.x * (mWindowHeight / 3) + 15, mAiImagePath) );
    }
}
