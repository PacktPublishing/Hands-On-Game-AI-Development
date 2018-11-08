//
//  LegacyGameCharacter.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 18/05/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#ifndef LegacyGameCharacter_hpp
#define LegacyGameCharacter_hpp

#include "GameObject.hpp"

#include "MovingObject.hpp"

class LegacyGameCharacter : public GameObject, public Observer
{
public:
    
    LegacyGameCharacter();
    virtual ~LegacyGameCharacter();
    
    virtual void actionEventCallback(ActionEvent pEvent) {}
    virtual void keyboardEventCallback(KeyboardEvents pEvent) {}
    virtual void mouseEventCallback(MouseEvents pEvent) {}
    
    virtual Texture* getVisual() const = 0;
    virtual LegacyCollider* getCollider() const = 0;
    virtual glm::vec2 getPosition() const = 0;
    virtual glm::vec2 getHeadingVector() const = 0;
    
    virtual void setPosition(const glm::vec2& pPos) = 0;
    
    virtual void Update() {}
    virtual void handleCollision(const LegacyCollider* pObj) {}

private:
    
};

#endif /* GameCharacter_hpp */
