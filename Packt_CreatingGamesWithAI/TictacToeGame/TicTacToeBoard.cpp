//
//  TicTacToeBoard.cpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 18/01/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#include "TicTacToeBoard.hpp"

TicTacToeBoard::TicTacToeBoard(const int pCellSize, const int pRowNum, const int pColNum)
    : mCellSize(pCellSize), mRowCount(pRowNum), mColCount(pColNum)
{
    // Init the field
    mGameField.resize(mRowCount);
    for(int row = 0; row < mRowCount; ++row)
    {
        mGameField[row].resize(mColCount);
    }
    
    reset();
}

TicTacToeBoard::~TicTacToeBoard()
{
    // Clear the field vector
    for(int row = 0; row < mRowCount; ++row)
    {
        mGameField[row].clear();
    }
    mGameField.clear();
}

void TicTacToeBoard::reset()
{
    // Fill the field
    for(int row = 0; row < mRowCount; ++row)
    {
        for(int col = 0; col <mColCount; ++col)
        {
            mGameField[row][col] = eFIELD_MOVES::eFM_EMPTY;
        }
    }
}

int TicTacToeBoard::getBoardRowSize() const
{
    return mRowCount;
}

int TicTacToeBoard::getBoardColSize() const
{
    return mColCount;
}

eFIELD_MOVES TicTacToeBoard::getGivenCellValue(const int pRow, const int pCol) const
{
    return mGameField[pRow][pCol];
}

void TicTacToeBoard::setGivenCellValue(const int pRow, const int pCol, const eFIELD_MOVES pType)
{
    mGameField[pRow][pCol] = pType;
}


eGAME_WINNER TicTacToeBoard::checkWinSituation(const eFIELD_MOVES pGamerType)
{
    eGAME_WINNER result = eGAME_WINNER::eGW_CONTINUE;
    int winCounter = 0;
    
    // Check diagonals (Win case)
    for(int diag = 0; diag < mRowCount; ++diag)
    {
        if( mGameField[diag][diag] != pGamerType)
        {
            winCounter = 0;
            break;
        }
        
        winCounter++;
    }
    
    if(winCounter == mRowCount)
    {
        if(pGamerType == eFIELD_MOVES::eFM_PLAYER)
        {
            return eGAME_WINNER::eGW_PLAYER;
        }
        else
        {
            return eGAME_WINNER::eGW_AI;
        }
    }
    
    for(int diagI = 0, diagII = mColCount - 1 ; diagII > -1; ++diagI, --diagII)
    {
        if( mGameField[diagI][diagII] != pGamerType)
        {
            winCounter = 0;
            break;
        }
        
        winCounter++;
    }
    
    if(winCounter == mRowCount)
    {
        if(pGamerType == eFIELD_MOVES::eFM_PLAYER)
        {
            return eGAME_WINNER::eGW_PLAYER;
        }
        else
        {
            return eGAME_WINNER::eGW_AI;
        }
    }
    
    // Check rows (Win case)
    for(int row = 0; row < mRowCount; ++row)
    {
        for(int col = 0; col < mColCount; ++col)
        {
            if( mGameField[row][col] != pGamerType)
            {
                break;
            }
            else
            {
                winCounter++;
            }
        }
        
        if(winCounter == mRowCount)
        {
            if(pGamerType == eFIELD_MOVES::eFM_PLAYER)
            {
                return eGAME_WINNER::eGW_PLAYER;
            }
            else
            {
                return eGAME_WINNER::eGW_AI;
            }
            
        }
        else
        {
            winCounter = 0;
        }
    }
    
    // Check cols (Win case)
    for(int col = 0; col < mRowCount; ++col)
    {
        for(int row = 0; row < mColCount; ++row)
        {
            if( mGameField[row][col] != pGamerType)
            {
                break;
            }
            else
            {
                winCounter++;
            }
        }
        
        if(winCounter == mRowCount)
        {
            if(pGamerType == eFIELD_MOVES::eFM_PLAYER)
            {
                return eGAME_WINNER::eGW_PLAYER;
            }
            else
            {
                return eGAME_WINNER::eGW_AI;
            }
        }
        else
        {
            winCounter = 0;
        }
    }
    
    if( isMovesLeft() )
    {
        return result;
    }
    
    
    return eGAME_WINNER::eGW_DRAW;
}


// Checks whether there is space left on the game board
// RETURN TRUE: There is space to play more
// RETURN FALSE: No space left on the board
bool TicTacToeBoard::isMovesLeft()
{
    for (int row = 0; row < mRowCount; row++)
    {
        for (int col = 0; col < mColCount; col++)
        {
            if (mGameField[row][col] == eFIELD_MOVES::eFM_EMPTY)
            {
                return true;
            }
        }
    }
    
    return false;
}
