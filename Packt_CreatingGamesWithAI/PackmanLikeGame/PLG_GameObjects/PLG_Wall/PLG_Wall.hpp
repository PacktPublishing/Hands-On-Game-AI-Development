//
//  PLG_Wall.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 23/09/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#ifndef PLG_Wall_hpp
#define PLG_Wall_hpp

#include "VisualObject.hpp"

// Visual PLG wall object
class PLG_Wall : public VisualObject
{
public:
    
    PLG_Wall(const int posX, const int posY)
        : VisualObject(posX, posY, TextureCommons::DEFAULT_Z_ORDER, "Images/PacmanLikeGame/wall.png")
    { }
    
    virtual ~PLG_Wall() { }
};

#endif /* PLG_Wall_hpp */
