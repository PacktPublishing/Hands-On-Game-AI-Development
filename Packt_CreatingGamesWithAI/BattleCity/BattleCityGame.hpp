//
//  BattleCityGame.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 25/02/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#ifndef BattleCityGame_hpp
#define BattleCityGame_hpp

#include "Application.hpp"

#include "BattleCityGameWorld.hpp"

class BattleCityGame : public Application
{
public:
    
     BattleCityGame();
    
    virtual ~BattleCityGame();
    
    void reset() override;
    
    void actionEventCallback(ActionEvent pEvent) override;
    void keyboardEventCallback(KeyboardEvents pEvent) override;
    
    void update() override;
    
protected:
    
    bool init() override;
    
private:
    
    BattleCityGameWorld mGameWorld;
};

#endif /* BattleCityGame_hpp */
