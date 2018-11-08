//
//  Wall.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 08/07/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#ifndef Wall_hpp
#define Wall_hpp

#include "BoxCollider.hpp"

#include "VisualObject.hpp"

#include <string>

class Wall : public VisualObject
{
public:
    
    Wall(const int posX, const int posY, const std::string& imagePath);
    virtual ~Wall();
    
    bool getIsAlive() const;
    
    LegacyCollider* getCollider() const;
    void OnCollision(const LegacyCollider* obj );
    
private:
    bool mIsAlive;
    std::unique_ptr<LegacyBoxCollider> mCollider;
};

#endif /* Wall_hpp */
