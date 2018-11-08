//
//  TankLocomotion.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 17/05/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#ifndef TankLocomotion_hpp
#define TankLocomotion_hpp

#include "Locomotion.hpp"
#include "Tank.hpp"

class TankLocomotion : public LegacyLocomotion<Tank>
{
public:
    
    TankLocomotion();
    TankLocomotion(Tank* pTank);
    virtual ~TankLocomotion();
    
    virtual void turnLeft();
    virtual void turnRight();
    virtual void moveForward();
    virtual void moveBackward();
    
private:
    
    
};

#endif /* TankLocomotion_hpp */
