//
//  PLG_EnemyCharacter.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 24/09/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#ifndef PLG_EnemyCharacter_hpp
#define PLG_EnemyCharacter_hpp

#include "PLG_CircleCharacter.hpp"

class PLG_EnemyCharacter : public PLG_CircleCharacter
{
public:
    
    PLG_EnemyCharacter();
    virtual ~PLG_EnemyCharacter();
    
private:
    
    void performInit(const int pArgNumber, va_list args) override;
};

#endif /* PLG_EnemyCharacter_hpp */
