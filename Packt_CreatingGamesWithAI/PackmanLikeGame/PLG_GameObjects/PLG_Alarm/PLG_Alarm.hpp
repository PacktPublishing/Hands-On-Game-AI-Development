//
//  PLG_Alarm.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 02/11/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#ifndef PLG_Alarm_hpp
#define PLG_Alarm_hpp

#include "VisualObject.hpp"

class PLG_Alarm : public VisualObject
{
public:
    
    PLG_Alarm(const int pPosX, const int pPosY)
        : VisualObject(pPosX, pPosY, TextureCommons::DEFAULT_Z_ORDER, "Images/PacmanLikeGame/alarm.png")
    { }
    
    virtual ~PLG_Alarm() { }
};

#endif /* PLG_Alarm_hpp */
