//
//  AnimateTexture.cpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 30/05/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#include "AnimateTexture.hpp"

#include "Timer.hpp"

AnimateTexture::AnimateTexture(
                                const int pTotalFrame,
                                const float pAnimationDuration,
                                const int pWidth, const int pHeight,
                                const std::string& pAtlasPath,
                                const bool pIsLoop
                               )
    :   Texture(pAtlasPath),
        mTotalFrame(pTotalFrame), mAnimationDuration(pAnimationDuration),
        mIsplaying(false), mIsLoop(pIsLoop), mCurrentFrame(0), mCurrentAnimationTime(0.f)
{
    InitAnimationBasics(pWidth, pHeight);
}

AnimateTexture::AnimateTexture(
                                const int pTotalFrame,
                                const float pAnimationDuration,
                                const int pWidth, const int pHeight,
                                const int pZOrder, const std::string& pAtlasPath,
                                const bool pIsLoop
                               )
    :   Texture(pZOrder, pAtlasPath),
        mTotalFrame(pTotalFrame), mAnimationDuration(pAnimationDuration),
        mIsplaying(false), mIsLoop(pIsLoop), mCurrentFrame(0), mCurrentAnimationTime(0.f)
{
    InitAnimationBasics(pWidth, pHeight);
}

AnimateTexture::AnimateTexture(
                                const int pTotalFrame,
                                const float pAnimationDuration,
                                const int pWidth, const int pHeight,
                                const int pScreenX, const int pScreenY, const std::string& pAtlasPath,
                                const bool pIsLoop
                               )
    :   Texture(pScreenX, pScreenY, pAtlasPath),
        mTotalFrame(pTotalFrame), mAnimationDuration(pAnimationDuration),
        mIsplaying(false), mIsLoop(pIsLoop), mCurrentFrame(0), mCurrentAnimationTime(0.f)
{
    InitAnimationBasics(pWidth, pHeight);
}

AnimateTexture::AnimateTexture(
                                const int pTotalFrame,
                                const float pAnimationDuration,
                                const int pWidth, const int pHeight,
                                const int pScreenX, const int pScreenY, const int pZOrder, const std::string& pAtlasPath,
                                const bool pIsLoop
                               )
    :   Texture(pScreenX, pScreenY, pZOrder, pAtlasPath),
        mTotalFrame(pTotalFrame), mAnimationDuration(pAnimationDuration),
        mIsplaying(false), mIsLoop(pIsLoop), mCurrentFrame(0), mCurrentAnimationTime(0.f)
{
    InitAnimationBasics(pWidth, pHeight);
}

AnimateTexture::~AnimateTexture()
{
    
}

void AnimateTexture::InitAnimationBasics(const int pWidth, const int pHeight)
{
    mNextFrameTime = mAnimationDuration / mTotalFrame;
    
    // Because, Texture::loadImage() will assign
    // the whole width and height
    mWidth = pWidth;
    mHeight = pHeight;
}

int AnimateTexture::getImagePosX() const {   return mWidth * mCurrentFrame; }
int AnimateTexture::getImagePosY() const {   return mHeight * 0; }   //TODO INTRODUCE CURRENT ROW!!!

bool AnimateTexture::isLoop() const { return mIsLoop; }
void AnimateTexture::setLoop() { mIsLoop = true; }
void AnimateTexture::clearLoop() { mIsLoop = false; }

bool AnimateTexture::isPlaying()
{
    return mIsplaying;
}

int AnimateTexture::getCurrentFrame()
{
    return mCurrentFrame;
}

void AnimateTexture::update()
{
    if(mIsplaying)
    {
        mCurrentAnimationTime += Time.deltaTime;
        if(mCurrentAnimationTime > mNextFrameTime)
        {
            callNextFrame();
        }
    }
}

void AnimateTexture::startAnimation()
{
    mIsplaying = true;
}
void AnimateTexture::pauseAnimation()
{
    mIsplaying = false;
}

void AnimateTexture::stopAnimation()
{
    mIsplaying = false;
    
    mCurrentFrame = 0;
    mCurrentAnimationTime = 0.f;
}

void AnimateTexture::callNextFrame()
{
    mCurrentFrame++;
    if(mCurrentFrame >= mTotalFrame)
    {
        if(!mIsLoop)
        {
            stopAnimation();
        }
        else
        {
            mCurrentFrame = 0;
        } 
    }
    
    mCurrentAnimationTime = 0.f;
}
