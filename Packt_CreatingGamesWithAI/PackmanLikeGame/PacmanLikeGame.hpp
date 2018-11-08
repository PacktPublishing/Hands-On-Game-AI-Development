//
//  PackmanLikeGame.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 13/09/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#ifndef PacmanLikeGame_hpp
#define PacmanLikeGame_hpp

#include "Application.hpp"

#include "PLG_GameWorld.hpp"

class PacmanLikeGame : public Application
{
public:
    
    PacmanLikeGame();
    virtual ~PacmanLikeGame() { }
    
    void reset() override;
    
    void actionEventCallback(ActionEvent pEvent) override;
    void mouseEventCallback(MouseEvents pEvent) override;
    void keyboardEventCallback(KeyboardEvents pEvent) override;
    
    void update() override;
    
private:
    
    bool init() override;

    PLG_GameWorld mGameWorld;
};

#endif /* PackmanLikeGame_hpp */
