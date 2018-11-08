//
//  GameWorldInfo.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 06/08/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#ifndef GameWorldInfo_hpp
#define GameWorldInfo_hpp

#include <vector>
#include "vec2.hpp"

#define GameInfo GameWorldInfo::getInstance()

class GameWorldInfo
{
public:
    
    static GameWorldInfo& getInstance();
    
    glm::vec2 playerPosition;
    // Id-position pairs for AIs
    std::vector<std::pair<int, glm::vec2>> aiPositions;
    
private:
    
    GameWorldInfo();
    ~GameWorldInfo();
    
};

#endif /* GameWorldInfo_hpp */
