//
//  TicTacToeGameModel.cpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 28/12/2017.
//  Copyright © 2017 Cihan Ozer. All rights reserved.
//

#include "TicTacToeGameModel.hpp"

#include "TicTacToeCommons.hpp"

#include <iostream>

///////////// CONSTRUCTOR - DESTRUCTOR /////////////

TicTacToeGameModel::TicTacToeGameModel(const int pCellSize, const int pRowColNum)
    : mCellSize(pCellSize), mRowColNum(pRowColNum)
{
    mGameField = std::make_unique<TicTacToeBoard>(mCellSize, mRowColNum, mRowColNum);
}

TicTacToeGameModel::~TicTacToeGameModel()
{

}

///////////// PUBLIC METHODS /////////////

void TicTacToeGameModel::reset()
{
    mGameField->reset();
}

bool TicTacToeGameModel::handlePlayerMove(const int pMouseX, const int pMouseY, glm::ivec2& pRowCol)
{
    // Convertion from pixels to game field row and col
    int row = std::max(0, (int)(pMouseY / mCellSize));
    int col = std::max(0, (int)(pMouseX / mCellSize));
    
    // Fill the field if not already filled
    if( mGameField->getGivenCellValue(row, col) == eFIELD_MOVES::eFM_EMPTY )
    {;
        mGameField->setGivenCellValue(row, col, eFIELD_MOVES::eFM_PLAYER);
        pRowCol.x = row;
        pRowCol.y = col;
        
        return true;
    }
    
    return false;
}

bool TicTacToeGameModel::handleAiMove(glm::ivec2& decision)
{
    decision = mAi.decide(mGameField.get());
    
    if( decision.x > -1 && decision.y > -1 )
    {
        mGameField->setGivenCellValue(decision.x, decision.y, eFIELD_MOVES::eFM_AI);
        return true;
    }
    
    return false;
    
}

eGAME_WINNER TicTacToeGameModel::checkPlayerWinCase()
{
    return mGameField->checkWinSituation(eFIELD_MOVES::eFM_PLAYER);
}

eGAME_WINNER TicTacToeGameModel::checkAiWinCase()
{
    return mGameField->checkWinSituation(eFIELD_MOVES::eFM_AI);
}
