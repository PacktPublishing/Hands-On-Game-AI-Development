//
//  Tank.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 18/05/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#ifndef Tank_hpp
#define Tank_hpp

#include "LegacyGameCharacter.hpp"
#include "MovingObject.hpp"
#include "BoxCollider.hpp"

class Tank : public MovingObject
{
public:
    
    Tank(LegacyGameCharacter* const pOwner, const std::string& pImagePath);
    Tank(LegacyGameCharacter* const pOwner, const float pPosX, const float pPosY, const float startRotationAngle, const std::string& pImagePath);
    virtual ~Tank();
    
    bool canMoveForward() const;
    bool canMoveBackward() const;
    
    LegacyCollider* getCollider() const;
    void OnCollision(const LegacyCollider* obj );

    void increaseRotation(const float pAngleDegrees);
    void decreaseRotation(const float pAngleDegrees);
    
    bool mCanMoveForward;
    bool mCanMoveBackward;
    
private:
    
    // In degrees
    float mRotationAngle;
    
    std::unique_ptr<LegacyBoxCollider> mCollider;
    
    LegacyGameCharacter* const mOwner;
    
    void bounceBack(const LegacyCollider* obj);
    void checkForBlock(const LegacyCollider* obj);
};

#endif /* Tank_hpp */
