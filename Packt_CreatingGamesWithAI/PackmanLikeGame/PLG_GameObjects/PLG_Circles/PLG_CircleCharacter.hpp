//
//  CircleCharacter.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 24/09/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#ifndef PLG_CircleCharacter_hpp
#define PLG_CircleCharacter_hpp

#include "GameCharacter.hpp"

class PLG_CircleCharacter : public GameCharacter<PLG_CircleCharacter>
{
public:
    
    PLG_CircleCharacter();
    virtual ~PLG_CircleCharacter();

    void callOnFrame() override;
    void callOnRender(std::vector<Texture*>& mTextures) override;
};

#endif /* PLG_CircleCharacter_hpp */
