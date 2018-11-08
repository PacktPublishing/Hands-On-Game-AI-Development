//
//  AnimateTexture.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 30/05/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#ifndef AnimateTexture_hpp
#define AnimateTexture_hpp

#include "Texture.hpp"

class AnimateTexture : public Texture
{
public:
    
    AnimateTexture(
                    const int pTotalFrame,
                    const float pAnimationDuration,
                    const int pWidth, const int pHeight,
                    const std::string& pAtlasPath,
                    const bool pIsLoop = true
                   );
    
    AnimateTexture(
                    const int pTotalFrame,
                    const float pAnimationDuration,
                    const int pWidth, const int pHeight,
                    const int pZOrder, const std::string& pAtlasPath,
                    const bool pIsLoop = true
                   );
    
    AnimateTexture(
                    const int pTotalFrame,
                    const float pAnimationDuration,
                    const int pWidth, const int pHeight,
                    const int pScreenX, const int pScreenY, const std::string& pAtlasPath,
                    const bool pIsLoop = true
                   );
    AnimateTexture(
                    const int pTotalFrame,
                    const float pAnimationDuration,
                    const int pWidth, const int pHeight,
                    const int pScreenX, const int pScreenY, const int pZOrder, const std::string& pAtlasPath,
                    const bool pIsLoop = true
                   );
    
    virtual ~AnimateTexture();
    
    virtual int getImagePosX() const;
    virtual int getImagePosY() const;
    
    bool isLoop() const;
    void setLoop();
    void clearLoop();
    
    bool isPlaying();
    int getCurrentFrame();
    
    void update();
    
    void startAnimation();
    void pauseAnimation();
    void stopAnimation();
    
private:
    
    void InitAnimationBasics(const int pWidth, const int pHeight);
    
    void callNextFrame();
    
    bool mIsplaying;
    bool mIsLoop;
    
    int mCurrentFrame;
    int mTotalFrame;
    
    float mCurrentAnimationTime;
    float mAnimationDuration;
    float mNextFrameTime;
};

#endif /* AnimateTexture_hpp */
