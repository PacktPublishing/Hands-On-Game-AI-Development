//
//  PLG_KeyController.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 02/11/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#ifndef PLG_KeyController_hpp
#define PLG_KeyController_hpp

#include "GameCharacterController.hpp"
#include "PLG_Key.hpp"

class PLG_KeyController : public GameCharacterController
{
public:
    
    PLG_KeyController(const float pPosX, const float pPosY);
    virtual ~PLG_KeyController();
    
    void reset() override;
    
    void callOnRender(std::vector<Texture*>& mTextures) override;
    void onCollision(const Collider* pObject) override;
    
private:
    
    void performInit(const int pArgNumber, va_list args) override;
    
    bool mIsDisappeared;
    std::unique_ptr<PLG_Key> mVisual;
};

#endif /* PLG_KeyController_hpp */
