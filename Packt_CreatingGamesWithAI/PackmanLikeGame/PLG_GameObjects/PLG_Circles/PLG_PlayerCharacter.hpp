//
//  PLG_PlayerCharacter.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 24/09/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#ifndef PLG_PlayerCharacter_hpp
#define PLG_PlayerCharacter_hpp

#include "PLG_CircleCharacter.hpp"

class PLG_PlayerCharacter : public PLG_CircleCharacter
{
public:
    
    PLG_PlayerCharacter();
    virtual ~PLG_PlayerCharacter();
    
private:
    
    void performInit(const int pArgNumber, va_list args) override;
};

#endif /* PLG_PlayerCharacter_hpp */
