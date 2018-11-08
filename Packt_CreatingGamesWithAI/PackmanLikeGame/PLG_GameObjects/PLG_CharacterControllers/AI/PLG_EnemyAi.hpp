//
//  PLG_EnemyAi.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 01/10/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#ifndef PLG_EnemyAi_hpp
#define PLG_EnemyAi_hpp

#include "GameCharacterController.hpp"

#include "PLG_EnemyCharacter.hpp"
#include "StateMachine.hpp"
#include "PLG_EnemyAiStates.hpp"
#include "PathPlanner.hpp"

class PLG_EnemyAi : public GameCharacterController
{
public:
    
    enum eENEMY_STATES{ eES_SearchPlayer, eES_AlarmOthers, eES_WanderAround };
    
    // Base methods and constructors
    PLG_EnemyAi();
    PLG_EnemyAi(const float pPosX, const float pPosY);
    virtual ~PLG_EnemyAi() { }
    
    void reset() override;

    void callOnFrame() override;
    
    void callOnRender(std::vector<Texture*>& mTextures) override;
    
    void onCollision(const Collider* pObject) override;
    
    // Ai related methods
    bool isAlarmed() { return mIsAlarmed; }
    bool hasPositionTarget() { return mDoesHavePositionTarget; }
    
    bool isPlayerSeen() { return mCanSeePlayer; }
    bool isPlayerClose() { return mIsPlayerClose; }
    
    void changeState(const eENEMY_STATES pNewStateRequest);
    
    PathPlanner& getPathPlanner() { return mPathPlanner; }
    
    void chooseNewRandomPath();
    void setPathToAlarm();
    void setPathToPlayer();
    
    void attack() { }
    
private:
    
    void performInit(const int pArgNumber, va_list args) override;
    
    glm::vec2 getColliderMin();
    glm::vec2 getColliderMax();
    
    void monitorSelf();
    bool isAtThePosition(const glm::vec2& pPosI, const glm::vec2& pPosII);
    void startStoppingProcess(const glm::vec2& pPosition);
    
    void resetPathTracking();
    void handleMovement();
    void updateMovementDirection();
    
    void rewindPosition();
    
    bool mDoesHavePositionTarget;
    bool mCanSeePlayer;
    bool mIsPlayerClose;
    bool mIsAlarmed;

    bool mIsInStoppingProcess;
    int mPathPositionIndex;
    float mTimeToStop;
    float mCurrentStopTime;
    float mDecisionTimeLimit;
    float mCurrentDecisionTime;
    glm::vec2 mStopPosition;
    
    glm::vec2 mLastPos;
    
    PLG_EnemyCharacter mCharacter;
    PathPlanner mPathPlanner;
    
    PLG_EnemyWanderingState mWanderingState;
    PLG_EnemyAlarmOthersState mAlarmOthersState;
    PLG_EnemySearchPlayerState mSearchPlayerState;
    
    std::vector<glm::vec2> mPathPositions;
    StateMachine<PLG_EnemyAi> mStateMachine;
};

#endif /* PLG_EnemyAi_hpp */
