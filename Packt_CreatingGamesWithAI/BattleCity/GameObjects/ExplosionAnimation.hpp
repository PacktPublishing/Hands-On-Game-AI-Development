//
//  ExplosionAnimation.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 08/07/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#ifndef ExplosionAnimation_hpp
#define ExplosionAnimation_hpp

#include "AnimateTexture.hpp"

class ExplosionAnimation : public AnimateTexture
{
public:
    
    ExplosionAnimation();
    ExplosionAnimation(const glm::vec2& pPosition);
    virtual ~ExplosionAnimation();
    
    void getReady(const glm::vec2& pPosition);
};

#endif /* ExplosionAnimation_hpp */
