//
//  GameCharacterController.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 22/09/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#ifndef GameCharacterController_hpp
#define GameCharacterController_hpp

#include "Observer.hpp"
#include "IGameObject.hpp"

#include <memory>

class Collider;
class MovingObject;

// Each game character has a GameCharacterController
//
// Many GameCharacterControllers are managed by the related managers
class GameCharacterController : public IGameObject, public Observer
{
public:
    
    GameCharacterController()
        : mBoundingRadius(0.f)
    { }
    
    virtual ~GameCharacterController() { }
    
    glm::vec2 getPosition() const;
    glm::vec2 getCenterPosition() const;
    
    float getBoundingRadius() const { return mBoundingRadius; }
    void setBoundingRadius(const float pNewRadius) { mBoundingRadius = pNewRadius; }
    
    const Collider* getCollider() const { return mCollider.get(); }
    
    virtual void onCollision(const Collider* pObject) { }
    
    // Checks whether the agent can move to the given position from its current position
    bool canMoveTo(const glm::vec2& pPos);
    
    // Checks whether the agent can move between given position
    bool canMoveBetween(const glm::vec2& pFrom, const glm::vec2& pTo);
    
protected:
    
    // The magnitude of the object's bounding radius;
    float mBoundingRadius;
    
    MovingObject* mMovingObjectReference;
    
    std::unique_ptr<Collider> mCollider;
    
};

#endif /* GameCharacterController_hpp */
