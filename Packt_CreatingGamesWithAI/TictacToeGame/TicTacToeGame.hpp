//
//  TicTacToeGame.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 06/12/2017.
//  Copyright © 2017 Cihan Ozer. All rights reserved.
//

#ifndef TicTacToeGame_hpp
#define TicTacToeGame_hpp

#include "Texture.hpp"

#include "Application.hpp"

#include "TicTacToeGameModel.hpp"

#include "VisualObject.hpp"

class TicTacToeGame : public Application
{
public:

     TicTacToeGame();
    
    virtual ~TicTacToeGame();
    
    void reset();
    
    void actionEventCallback(ActionEvent pEvent);
    void keyboardEventCallback(KeyboardEvents pEvent);
    void mouseEventCallback(MouseEvents pEvent);
    
    void update();
    
protected:

    bool init();
    
    bool mIsQuit;
    
private:
    
    enum eMOVE_TURN{ eMT_PLAYER, eMT_PLAYER_WIN_CHECK, eMT_AI, eMT_AI_WIN_CHECK, eMT_count };
    
    eMOVE_TURN getTurn();
    void updateTurn();
    void evaluateTurn();
    
    void checkEndOfGameCase(const eGAME_WINNER pResult);
    
    void handleGameState();
    
    void makeGameOver(const std::string& pGameOverImagePath);
    
    void evaluatePlayerTurn(const int mouseX, const int mouseY);
    void evaluateAiTurn();
    
    eGAME_STATES mGameState;
    
    int mTurn;
    
    std::string mFieldImagePath;
    std::string mPlayerImagePath;
    std::string mAiImagePath;
    
    std::unique_ptr<TicTacToeGameModel> mGameModel;
    
    std::vector<std::unique_ptr<VisualObject>> mGameObjects;
    
    std::vector<std::unique_ptr<Texture>> mGameTextures;
};

#endif /* TicTacToeGame_hpp */
