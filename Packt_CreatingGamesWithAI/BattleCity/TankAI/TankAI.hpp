//
//  TankAI.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 06/08/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#ifndef TankAI_hpp
#define TankAI_hpp

#include "TankCommons.hpp"

#include "LegacyGameCharacter.hpp"
#include "TankCharacter.hpp"
#include "DT_DecisionTree.hpp"

class TankAI : public LegacyGameCharacter
{
public:
    
    TankAI(const glm::vec2& pDefultPos);
    virtual ~TankAI() {}
    
    bool getIsCollided() const;
    void clearIsCollided();
    Texture* getVisual() const override;

    LegacyCollider* getCollider() const override;
    glm::vec2 getPosition() const override;
    glm::vec2 getHeadingVector() const override;
    
    float getLastPathChangeTime() const;
    float getPathTimeLimit() const;
    void setLastPathTime(const float time);
    
    void setPosition(const glm::vec2& pPos) override;
    
    TankCommons::eTANK_MOVEMENT getCurrentMovement() const;
    void move(const TankCommons::eTANK_MOVEMENT pMovementDecision);
    void fire();
    
    void Update() override;
    void handleCollision(const LegacyCollider* pObj) override;
    
private:

    bool mIsStillMove;
    TankCommons::eTANK_MOVEMENT mFutureMove;
    
    bool mIsCollided;
    
    float mFireCoolDown;
    const float REFLEX_LIMIT = 0.25f;
    float mReflexTime;
    
    float mLastPathChangeTime;
    float mPathTimeLimit;
    
    glm::vec2 mDefultPos;
    
    std::unique_ptr<TankCharacter> mTankCharacter;
    
    std::unique_ptr<DecisionTree<TankAI>> mAi;
    
    void reset();
};

#endif /* TankAI_hpp */
