//
//  GameCharacter.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 24/09/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#ifndef GameCharacter_hpp
#define GameCharacter_hpp

#include "MovingObject.hpp"
#include "IGameObject.hpp"

#include "Locomotion.hpp"

// Base class that provides Locomotion for any moving object.
//
// GameCharacters are controlled via GameCharacterControllers
template <class character_type>
class GameCharacter : public MovingObject, public IGameObject
{
public:
    
    GameCharacter() : MovingObject() { }
    virtual ~GameCharacter() { }
    
    Locomotion<character_type>* getLocomotion() { return mLocomotion.get(); }
    
protected:
    
    std::unique_ptr<Locomotion<character_type>> mLocomotion;
};

#endif /* GameCharacter_hpp */
