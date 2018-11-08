//
//  MovingObject.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 15/05/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#ifndef MovingObject_hpp
#define MovingObject_hpp

#include "VisualObject.hpp"

class MovingObject : public VisualObject
{
public:
    
    MovingObject() : VisualObject() {}
    MovingObject(const std::string& pPath);
    MovingObject(const int pZOrder, const std::string& pPath);
    MovingObject(const int pScreenX, const int pScreenY, const std::string& pPath);
    MovingObject(const int pScreenX, const int pScreenY, const int pZOrder, const std::string& pPath);
    virtual ~MovingObject();
    
    Texture* getTexture();
    
    void setHeadingVector(const float pX, const float pY);
    void setHeadingVector(const float pAngleRotation);
    void setHeadingVector(const glm::vec2& pVector);
    glm::vec2 getHeadingVector() const;
    
    glm::vec2 getVelocity() const;
    
    void setDefaultSpeed(const float pDefaultSpeed);
    float getDefaultSpeed() const;
    
    // TODO add INIT()
    
protected:
    
    // A normalized vector pointing in the direction the entity is heading
    glm::vec2 mHeadingVector;

    // A vector perpendicular to the heading vector
    glm::vec2 mSideVector;
    
    // The maximum speed this entity may travel at.
    float MAX_SPEED;
    float mSpeed;
    glm::vec2 mVelocity;
    
};

#endif /* MovingObject_hpp */
