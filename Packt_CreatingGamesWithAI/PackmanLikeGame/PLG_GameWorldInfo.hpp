//
//  PLG_GameWorldInfo.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 10/10/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#ifndef PLG_GameWorldInfo_hpp
#define PLG_GameWorldInfo_hpp

#include "SparseGraph.hpp"
#include "NavGraphNode.hpp"
#include "GraphEdge.hpp"

#include <vector>
#include "vec2.hpp"

#define PLG_GameInfo PLG_GameWorldInfo::getInstance()
class PLG_GameWorldInfo
{
public:
    
    static PLG_GameWorldInfo& getInstance();
    
    bool isPlayerDown;
    bool isAlarmOn;
    
    glm::vec2 alarmPosition;
    glm::vec2 keyPosition;
    
    glm::vec2 playerPosition;
    
    
private:
    
    PLG_GameWorldInfo();
    ~PLG_GameWorldInfo();
    
};

#endif /* PLG_GameWorldInfo_hpp */
