//
//  Locomotion.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 17/05/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#ifndef Locomotion_hpp
#define Locomotion_hpp

#include "IGameObject.hpp"

template <class entity_type>
class Locomotion : public IGameObject
{
public:
    
    enum eTRANSLATION_DIRECTION{ eTD_CLEAR, eTD_FORWARD, eTD_BACKWARD, eTD_LEFT, eTD_RIGHT };
    enum eROTATION_DIRECTION{ eRD_CLEAR, eRD_X_POSI, eRD_X_NEG, eRD_Y_POSI, eRD_Y_NEG, eRD_Z_POSI, eRD_Z_NEG};
    
    Locomotion()
        :   mTranslationDirection(eTRANSLATION_DIRECTION::eTD_CLEAR),
            mRotationDirection(eROTATION_DIRECTION::eRD_CLEAR),
            mOwner(nullptr)
    { }
    Locomotion(entity_type* pOwner)
    :   mTranslationDirection(eTRANSLATION_DIRECTION::eTD_CLEAR),
    mRotationDirection(eROTATION_DIRECTION::eRD_CLEAR),
    mOwner(pOwner)
    { }
    virtual ~Locomotion() { }
    
    void callOnFrame() override
    {
        applyRotation();
        applyTranslation();
    }

    void setMovement(const eTRANSLATION_DIRECTION pDirection) {  mTranslationDirection = pDirection; }
    void setRotation(const eROTATION_DIRECTION pDirection) { mRotationDirection = pDirection; }
    
    void clearMovement() { mTranslationDirection = eTRANSLATION_DIRECTION::eTD_CLEAR; }
    void clearRotation() { mRotationDirection = eROTATION_DIRECTION::eRD_CLEAR; }
    
protected:

    eTRANSLATION_DIRECTION mTranslationDirection;
    eROTATION_DIRECTION mRotationDirection;
    
    entity_type* mOwner;
    
private:
    
    void performInit(const int pArgNumber, va_list args) override
    {
        // TODO Solve this
//        mOwner = va_arg(args, entity_type);
    }
    
    virtual void applyRotation() = 0;
    virtual void applyTranslation() = 0;
};


template <class entity_type>
class LegacyLocomotion
{
public:
    
    LegacyLocomotion()
        : mObject(nullptr)
    {
        
    }
    
    LegacyLocomotion(entity_type* pObject)
    {
        mObject = pObject;
    }
    
    virtual ~LegacyLocomotion()
    {
        mObject = nullptr;
    }
    
    void setObject(entity_type* pObject)
    {
        mObject = pObject;
    }
    
    virtual void turnLeft() = 0;
    virtual void turnRight() = 0;
    virtual void moveForward() = 0;
    virtual void moveBackward() = 0;
    
protected:
    
    entity_type* mObject;
    
};

#endif /* Locomotion_hpp */
