//
//  PLG_AlarmController.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 02/11/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#ifndef PLG_AlarmController_hpp
#define PLG_AlarmController_hpp

#include "GameCharacterController.hpp"
#include "PLG_Alarm.hpp"

class PLG_AlarmController : public GameCharacterController
{
public:
    
    PLG_AlarmController(const float pPosX, const float pPosY);
    virtual ~PLG_AlarmController();
    
    void reset() override;
    
    void callOnRender(std::vector<Texture*>& mTextures) override;
    void onCollision(const Collider* pObject) override;
    
private:
    
    void performInit(const int pArgNumber, va_list args) override;
    
    bool mIsDisappeared;
    std::unique_ptr<PLG_Alarm> mVisual;
};
#endif /* PLG_AlarmController_hpp */
