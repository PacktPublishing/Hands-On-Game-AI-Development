//
//  BoxCollider.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 10/07/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#ifndef BoxCollider_hpp
#define BoxCollider_hpp

#include "Collider.hpp"

// Axis-aligned bounding box collider
//
// TODO Decouple AABB part for the BboxCollider and inherit from both
//        Collider and AABB
class BoxCollider : public Collider
{
public:
    
    BoxCollider(const unsigned int pColliderType, GameCharacterController* pOwner);
    BoxCollider(const unsigned int pColliderType, GameCharacterController* pOwner, const glm::vec2& pMin, const glm::vec2& pMax);
    
    virtual ~BoxCollider();

    // TODO UPDATE THIS FOR SUPPORTING BOTH AABB AND SPHERICAL
    bool checkCollision(const Collider* obj) const;
    bool checkCollision(const glm::vec2& point) const;
    const glm::vec2& getMinPos() const;
    const glm::vec2& getMaxPos() const;
    float getWidth() const;
    float getHeight() const;
    float getDepth() const { return 0; }
    
};

//////////////////////////// LEGACY CODE THAT SHALL BE GONE SOON //////////////////////////////////

class LegacyBoxCollider : public LegacyCollider
{
public:
    
    LegacyBoxCollider(const unsigned int pColliderType, VisualObject* pOwner)
        : LegacyBoxCollider::LegacyCollider(pColliderType, pOwner)
    { }
    
    LegacyBoxCollider(const unsigned int pColliderType, VisualObject* pOwner, const int pWidth, const int pHeight)
        : LegacyBoxCollider::LegacyCollider(pColliderType, pOwner, pWidth, pHeight)
    { }
    
    virtual ~LegacyBoxCollider()
    {}
    
    bool checkCollision(const LegacyCollider* obj) const
    {
        // Axis-aligned 2D bounding box (Bbox) collision detection
        if ( LegacyBoxCollider::getBboxTopLeft().x < (obj->getBboxTopLeft().x + obj->getWidth()) &&
            (LegacyBoxCollider::getBboxTopLeft().x + LegacyBoxCollider::getWidth())> obj->getBboxTopLeft().x &&
            LegacyBoxCollider::getBboxTopLeft().y < (obj->getBboxTopLeft().y + obj->getHeight()) &&
            (LegacyBoxCollider::getBboxTopLeft().y + LegacyBoxCollider::getHeight()) > obj->getBboxTopLeft().y
            )
        {
            return true;
        }
        
        return false;
    }
};

#endif /* BoxCollider_hpp */
