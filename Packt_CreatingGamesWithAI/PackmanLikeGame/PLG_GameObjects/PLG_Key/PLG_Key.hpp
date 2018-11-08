//
//  PLG_Key.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 02/11/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#ifndef PLG_Key_hpp
#define PLG_Key_hpp

#include "VisualObject.hpp"

class PLG_Key : public VisualObject
{
public:
    
    PLG_Key(const int pPosX, const int pPosY)
        : VisualObject(pPosX, pPosY, TextureCommons::DEFAULT_Z_ORDER, "Images/PacmanLikeGame/key.png")
    { }
    
    virtual ~PLG_Key() { } 
};

#endif /* PLG_Key_hpp */
