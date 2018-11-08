//
//  PLG_Player.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 24/09/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#ifndef PLG_Player_hpp
#define PLG_Player_hpp

#include "GameCharacterController.hpp"

#include "PLG_PlayerCharacter.hpp"
#include "PathPlanner.hpp"

class PLG_Player : public GameCharacterController
{
public:
    
    PLG_Player();
    PLG_Player(const float pPosX, const float pPosY);
    virtual ~PLG_Player();

    void reset() override;
    
    void callOnFrame() override;
    void callOnRender(std::vector<Texture*>& mTextures) override;
    
    void mouseEventCallback(MouseEvents pEvent) override;
    
    void onCollision(const Collider* pObject) override;
    
private:
    
    glm::vec2 getColliderMin();
    glm::vec2 getColliderMax();
    
    void performInit(const int pArgNumber, va_list args) override;
    
    bool isAtThePosition(const glm::vec2& pPosI, const glm::vec2& pPosII);
    void handleMovement();
    void resetPathTracking();
    void updateMovementDirection();
    void startStoppingProcess(const glm::vec2& pPosition);
    
    void rewindPosition();
    
    glm::vec2 mLastPos;
    
    PLG_PlayerCharacter mCharacter;
    
    bool mDidArrive;
    bool mIsHandleInput;
    bool mIsInStoppingProcess;
    int mPathPositionIndex;
    float mTimeToStop;
    float mCurrentStopTime;
    glm::vec2 mCommanedPosition;
    glm::vec2 mStopPosition;
    std::vector<glm::vec2> mPathPositions;
    PathPlanner mPathPlanner;
    
    
    
};

#endif /* PLG_Player_hpp */
