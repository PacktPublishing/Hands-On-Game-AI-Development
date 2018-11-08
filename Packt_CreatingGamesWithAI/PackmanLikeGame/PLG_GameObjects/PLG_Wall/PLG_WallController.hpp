//
//  PLG_WallController.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 23/09/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#ifndef PLG_WallController_hpp
#define PLG_WallController_hpp

#include "GameCharacterController.hpp"

#include "PLG_Wall.hpp"

class PLG_WallController : public GameCharacterController
{
public:
    
    PLG_WallController(const int posX, const int posY);
    virtual ~PLG_WallController();
    
    void callOnFrame() override;

    void callOnRender(std::vector<Texture*>& mTextures) override;
    
    void onCollision(const Collider* pObject) override { }
    
private:
    
    void performInit(const int pArgNumber, va_list args) override;
    
    std::unique_ptr<PLG_Wall> mVisual;
};

#endif /* PLG_WallController_hpp */
