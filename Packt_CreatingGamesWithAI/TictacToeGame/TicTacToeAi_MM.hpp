//
//  TicTacToeAi_MM.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 28/12/2017.
//  Copyright © 2017 Cihan Ozer. All rights reserved.
//

#ifndef TicTacToeAi_MM_hpp
#define TicTacToeAi_MM_hpp

#include "Commons.hpp"

#include <vector>

#include "TicTacToeBoard.hpp"

#include "vec2.hpp"

class TicTacToeAi_MM
{ 
public:
    
    // Perform the decision process and return the best move (as row and column indices) found
    glm::ivec2 decide(TicTacToeBoard* pGameField);
    
private:
    
    // This will return the best possible move for the agent
    glm::ivec2 findBestMove(TicTacToeBoard* pGameField);
    
    int minimax(TicTacToeBoard*, int depth, bool isMax);
    // Evaluation function of minimax algorithm: Evaluate the current game state
    // and return the respected state result
    int evaluate(TicTacToeBoard* pGameField);
};

#endif /* TicTacToeAi_MM_hpp */
