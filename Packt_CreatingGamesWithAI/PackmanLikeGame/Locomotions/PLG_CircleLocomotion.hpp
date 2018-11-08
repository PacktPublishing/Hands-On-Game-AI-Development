//
//  PLG_CircleLocomotion.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 28/09/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#ifndef PLG_CircleLocomotion_hpp
#define PLG_CircleLocomotion_hpp

#include "Locomotion.hpp"
#include "PLG_CircleCharacter.hpp"

class PLG_CircleLocomotion : public Locomotion<PLG_CircleCharacter>
{
public:
    
    PLG_CircleLocomotion();
    PLG_CircleLocomotion(PLG_CircleCharacter* pOwner);
    virtual ~PLG_CircleLocomotion() { }
    
private:
    
    void applyRotation() override;
    void applyTranslation() override;
    
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

};

#endif /* PLG_CircleLocomotion_hpp */

