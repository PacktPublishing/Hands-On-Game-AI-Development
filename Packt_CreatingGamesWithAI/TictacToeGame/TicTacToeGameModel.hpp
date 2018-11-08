//
//  TicTacToeGameModel.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 28/12/2017.
//  Copyright © 2017 Cihan Ozer. All rights reserved.
//

#ifndef TicTacToeGameModel_hpp
#define TicTacToeGameModel_hpp

#include "Commons.hpp"
#include "TicTacToeCommons.hpp"

#include "TicTacToeAi_MM.hpp"
#include "TicTacToeBoard.hpp"

class TicTacToeGameModel
{
public:
    
    TicTacToeGameModel(const int pCellSize, const int pRowColNum);
    ~TicTacToeGameModel();
    
    void reset();

    bool handlePlayerMove(const int pMouseX, const int pMouseY, glm::ivec2& pRowCol);
    bool handleAiMove(glm::ivec2& decision);
    
    eGAME_WINNER checkPlayerWinCase();
    eGAME_WINNER checkAiWinCase();
    
private:
    
    int mCellSize;
    int mRowColNum;
    
    std::unique_ptr<TicTacToeBoard> mGameField;
    
    TicTacToeAi_MM mAi;
};

#endif /* TicTacToeGameModel_hpp */
