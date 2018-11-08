//
//  CollidingObject.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 19/06/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#ifndef CollidingObject_hpp
#define CollidingObject_hpp

#include "GameCharacterController.hpp"

#include "vec2.hpp"

// Base Collider class
class Collider
{
public:
    
    enum eINTERNAL_COLLIDER_TYPE{ BOX, SPHERE };
    
    Collider(const unsigned int pInternalType, const unsigned int pColliderType, GameCharacterController* pOwner)
    : mIsCollided(false), mInternalColliderType(pInternalType), mColliderType(pColliderType), mOwner(pOwner)
    { }
    
    virtual ~Collider() { mOwner = nullptr; }
    
    virtual bool checkCollision(const Collider* obj) const = 0;
    virtual bool checkCollision(const glm::vec2& point) const = 0;
    virtual const glm::vec2& getMinPos() const = 0;
    virtual const glm::vec2& getMaxPos() const = 0;
    virtual float getWidth() const = 0;
    virtual float getHeight() const = 0;
    virtual float getDepth() const = 0;
    
    void setMinPos(const glm::vec2& pMin) { mMin = pMin; }
    void setMaxPos(const glm::vec2& pMax) { mMax = pMax; }
    
    virtual void collide(const Collider* obj) const
    {
        mOwner->onCollision(obj);
    }
    
    bool IsCollided() const { return mIsCollided; }
    void setCollided() { mIsCollided = true; }
    void clearCollided() { mIsCollided = false; }
    
    unsigned int getType() const { return mColliderType; }
    unsigned int getInternalType() const { return mInternalColliderType; }
    
protected:
    
    bool mIsCollided;
    
    unsigned int mColliderType;
    unsigned int mInternalColliderType;
    
    glm::vec2 mMax, mMin;
    
    GameCharacterController* mOwner;
};


//////////////////////////// LEGACY CODE THAT SHALL BE GONE SOON //////////////////////////////////

class VisualObject;

class LegacyCollider
{
public:
    
    LegacyCollider(const unsigned int pColliderType, VisualObject* pOwner);
    LegacyCollider(const unsigned int pColliderType, VisualObject* pOwner, const int pWidth, const int pHeight);
    
    virtual ~LegacyCollider()
    {}
    
    virtual bool checkCollision(const LegacyCollider* obj) const = 0;
    virtual void collide(const LegacyCollider* obj) const;
    
    bool IsCollided() const { return mIsCollided; }
    void setCollided() { mIsCollided = true; }
    void clearCollided() { mIsCollided = false; }
    
    unsigned int getType() const { return mColliderType; }
    
    float getWidth() const { return mWidth; }
    float getHeight() const { return mHeight; }
    
    glm::vec2 getBboxTopLeft() const;
    glm::vec2 getBboxDownRight() const;
    
private:
    
    bool mIsCollided;
    
    int mWidth, mHeight;
    
    unsigned int mColliderType;
    
    VisualObject* mOwner;
};

#endif /* CollidingObject_hpp */
