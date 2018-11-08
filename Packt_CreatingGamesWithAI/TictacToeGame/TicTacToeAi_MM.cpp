//
//  TicTacToeAi_MM.cpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 28/12/2017.
//  Copyright © 2017 Cihan Ozer. All rights reserved.
//

#include "TicTacToeAi_MM.hpp"

#include "TicTacToeCommons.hpp"

// Scores for the evaluation function
const int WIN_SCORE = 10;
const int LOSE_SCORE = -10;
const int DRAW_SCORE = 0;

// Perform the decision process and return the best move (as row and column indices) found
glm::ivec2 TicTacToeAi_MM::decide(TicTacToeBoard* pGameField)

{
    return findBestMove(pGameField);
}

// This will return the best possible move for the agent
glm::ivec2 TicTacToeAi_MM::findBestMove(TicTacToeBoard* pGameField)
{
    int minimaxScore = -1000;    // The score calculated by minimax algorithm's evaluation function
    glm::ivec2 bestMove;  // Row and column information of the best possible move
    bestMove.x = -1;
    bestMove.y = -1;
    
    // Traverse all cells, evalutae minimax function for the empty ones,
    // and return the cell with the best possible minimax score.
    for (int row = 0; row < pGameField->getBoardRowSize(); row++)
    {
        for (int col = 0; col < pGameField->getBoardColSize(); col++)
        {
            // Check if the celll is empty
            if (pGameField->getGivenCellValue(row, col) == eFIELD_MOVES::eFM_EMPTY)
            {
                // Make the move
                pGameField->setGivenCellValue(row, col, eFIELD_MOVES::eFM_AI);
                
                // Perform minimax algorithm and get the score
                int moveScore = minimax(pGameField, 0, false);
                
                // Undo the move
                pGameField->setGivenCellValue(row, col, eFIELD_MOVES::eFM_EMPTY);
                
                // If the score of the current move is better,
                // then update best possible move
                if (moveScore > minimaxScore)
                {
                    bestMove.x = row;
                    bestMove.y = col;
                    minimaxScore = moveScore;
                }
                
            }   // End of IF the cell is empty
        }
    }
    
    return bestMove;
}

int TicTacToeAi_MM::minimax(TicTacToeBoard* pGameField, int depth, bool isMax)
{
    // Evaluate the game states
    int score = evaluate(pGameField);
    
    // Return the maximer's score
    if (score == WIN_SCORE)
    {
        return score - depth;
    }
    
    // Return the minimizer's score
    if (score == LOSE_SCORE)
    {
        return score - depth;
    }
    
    // The game is draw case: No winner, no more moves left
    if( pGameField->isMovesLeft() == false)
    {
        return 0;
    }
    
    if (isMax)
    {
        // Maximizer's turn
        
        int bestScore = -1000;
        
        // Traverse all cells
        for (int row = 0; row < pGameField->getBoardRowSize(); row++)
        {
            for (int col = 0; col < pGameField->getBoardColSize(); col++)
            {
                // Check if a cell is empty
                if (pGameField->getGivenCellValue(row, col) == eFIELD_MOVES::eFM_EMPTY)
                {
                    // Make the move
                    pGameField->setGivenCellValue(row, col, eFIELD_MOVES::eFM_AI);
                    
                    // Call minimax recursively to calculate the score for maximizer
                    bestScore = std::max( bestScore, minimax(pGameField, depth + 1, !isMax) );
                    
                    // Undo the move
                    pGameField->setGivenCellValue(row, col, eFIELD_MOVES::eFM_EMPTY);
                }
            }
        }
        
        return bestScore;
    }
    else
    {
        // Minimizer's turn
        
        int bestScore = 1000;
        
        // Traverse all cells
        for (int row = 0; row < pGameField->getBoardRowSize(); row++)
        {
            for (int col = 0; col < pGameField->getBoardColSize(); col++)
            {
                // Check if a cell is empty
                if (pGameField->getGivenCellValue(row, col) == eFIELD_MOVES::eFM_EMPTY)
                {
                    // Make the move
                    pGameField->setGivenCellValue(row, col, eFIELD_MOVES::eFM_PLAYER);
                    
                    // Call minimax recursively to calculate the score for minimizer
                    bestScore = std::min(bestScore, minimax(pGameField, depth + 1, !isMax));
                    
                    // Undo the move
                    pGameField->setGivenCellValue(row, col, eFIELD_MOVES::eFM_EMPTY);
                }
            }
        }
        
        return bestScore;
    }
    
} // End of minimax()

// Evaluation function of minimax algorithm: Evaluate the current game state
// and return the respected state result
int TicTacToeAi_MM::evaluate(TicTacToeBoard* pGameField)
{
    // Checking the rows for the victory.
    for (int row = 0; row < pGameField->getBoardRowSize(); row++)
    {
        bool winCase = pGameField->getGivenCellValue(row, 0) == pGameField->getGivenCellValue(row, 1);
        for(int col = 1; col < pGameField->getBoardColSize() - 1; ++col)
        {
            winCase = winCase && pGameField->getGivenCellValue(row, col) == pGameField->getGivenCellValue(row, col + 1);
        }

        if(winCase)
        {
            if ( pGameField->getGivenCellValue(row, 0) == eFIELD_MOVES::eFM_AI)
            {
                return WIN_SCORE;
            }
            else if ( pGameField->getGivenCellValue(row, 0) == eFIELD_MOVES::eFM_PLAYER)
            {
                return LOSE_SCORE;
            }
        }
    }

    // Checking the columns for the victory.
    for (int col = 0; col < pGameField->getBoardColSize(); col++)
    {
        bool winCase = pGameField->getGivenCellValue(0, col) == pGameField->getGivenCellValue(1, col);
        for(int row = 1; row < pGameField->getBoardRowSize() - 1; ++row)
        {
            winCase = winCase && pGameField->getGivenCellValue(row, col) == pGameField->getGivenCellValue(row + 1, col);
        }

        if(winCase)
        {
            if (pGameField->getGivenCellValue(0, col) == eFIELD_MOVES::eFM_AI)
            {
                return WIN_SCORE;
            }
            else if (pGameField->getGivenCellValue(0, col) == eFIELD_MOVES::eFM_PLAYER)
            {
                return LOSE_SCORE;
            }
        }
    }

    bool winCase = pGameField->getGivenCellValue(0, 0) == pGameField->getGivenCellValue(1, 1);
    for(int diag = 1; diag < pGameField->getBoardRowSize() - 1; ++diag)
    {
        winCase = winCase && pGameField->getGivenCellValue(diag, diag) == pGameField->getGivenCellValue(diag + 1, diag + 1);
    }

    // Checking the diagonals for the victory.
    if(winCase)
    {
        if (pGameField->getGivenCellValue(0, 0) == eFIELD_MOVES::eFM_AI)
        {
            return WIN_SCORE;
        }
        else if (pGameField->getGivenCellValue(0, 0) == eFIELD_MOVES::eFM_PLAYER)
        {
            return LOSE_SCORE;
        }
    }

    winCase = pGameField->getGivenCellValue(0, pGameField->getBoardColSize() - 1 ) == pGameField->getGivenCellValue(1, pGameField->getBoardColSize() - 2);
    for(int diagI = 1, diagII = pGameField->getBoardColSize() - 2 ; diagII > 0; ++diagI, --diagII)
    {
        winCase = winCase && pGameField->getGivenCellValue(diagI, diagII) == pGameField->getGivenCellValue(diagI + 1, diagII - 1);
    }

    if(winCase)
    {
        if ( pGameField->getGivenCellValue(0, pGameField->getBoardColSize() - 1) == eFIELD_MOVES::eFM_AI )
        {
            return WIN_SCORE;
        }
        else if ( pGameField->getGivenCellValue(0, pGameField->getBoardColSize() - 1) == eFIELD_MOVES::eFM_PLAYER)
        {
            return LOSE_SCORE;
        }
    }
    
    // if there is no win, then it is a draw
    return DRAW_SCORE;
}
