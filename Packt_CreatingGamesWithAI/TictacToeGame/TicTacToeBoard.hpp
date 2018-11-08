//
//  TicTacToeBoard.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 18/01/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#ifndef TicTacToeBoard_hpp
#define TicTacToeBoard_hpp

#include "TicTacToeCommons.hpp"

#include <vector>

class TicTacToeBoard
{
public:
    
    TicTacToeBoard(const int pCellSize, const int pRowNum, const int pColNum);
    ~TicTacToeBoard();
    
    void reset();
    
    int getBoardRowSize() const;
    int getBoardColSize() const;

    eFIELD_MOVES getGivenCellValue(const int pRow, const int pCol) const;
    void setGivenCellValue(const int pRow, const int pCol, const eFIELD_MOVES pType);
    
    eGAME_WINNER checkWinSituation(const eFIELD_MOVES pGamerType);
    
    // Checks whether there is space left on the game board
    bool isMovesLeft();
    
private:
    
    int mCellSize;
    int mRowCount, mColCount;
    
    std::vector<std::vector<eFIELD_MOVES>> mGameField;
    
};

#endif /* TicTacToeBoard_hpp */
