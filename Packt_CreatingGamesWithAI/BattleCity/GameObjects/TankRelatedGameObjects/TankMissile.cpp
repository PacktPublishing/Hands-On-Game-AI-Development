//
//  TankMissile.cpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 22/06/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#include "TankMissile.hpp"

#include "Timer.hpp"
#include "TankMissileManager.hpp"

TankMissile::TankMissile()
: MovingObject(TextureCommons::DEFAULT_Z_ORDER, "Images/BattleCity/missile.png"), mIsFired(false)
{
    mSpeed = MAX_MISSILE_SPEED;
    mTexture->setWidth(MISSILE_TEXTURE_WIDTH);
    mTexture->setHeight(MISSILE_TEXTURE_HEIGHT);
    
    mCollider = std::make_unique<LegacyBoxCollider>((unsigned int)eTankColliderTypes::eCT_Bullet, this);
}

TankMissile::~TankMissile()
{

}

void TankMissile::reset()
{
    mIsFired = false;
}

bool TankMissile::isFired()
{
    return mIsFired;
}

void TankMissile::destructSelf()
{
    TankMissileManager::getInstance().requestExplosion( getPosition() );
    reset();
}

LegacyCollider* TankMissile::getCollider() const
{
    return mCollider.get();
}

void TankMissile::OnCollision(const LegacyCollider *obj)
{
    switch ( (eTankColliderTypes)obj->getType() )
    {
        case eCT_Bullet:
        case eCT_Tank:
        case eCT_Wall:
            // TODO Add explosion anim!
            destructSelf();
            break;
        default:
            break;
    }
}

void TankMissile::fire(const glm::vec2& pTankPosition, const glm::vec2& pTankHeadingVector)
{
    mIsFired = true;
    mHeadingVector = pTankHeadingVector;
    // 1.f is an arbitrary number to prevent the tank to shoot itself when it fires
    mPosition = pTankPosition + (mHeadingVector * (float)MISSILE_TEXTURE_WIDTH * 1.f);
}

void TankMissile::projectile()
{
    if(mIsFired)
    {
        mPosition =  mPosition + (mHeadingVector * mSpeed * Time.deltaTime);
        // Border check
        if(mPosition.x < 0 || mPosition.x > WINDOW_WIDTH || mPosition.y < 0 || mPosition.y > WINDOW_HEIGHT )
        {
            destructSelf();
        }
    }
}
