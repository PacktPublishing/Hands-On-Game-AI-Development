//
//  Texture.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 18/12/2017.
//  Copyright © 2017 Cihan Ozer. All rights reserved.
//

#ifndef Texture_hpp
#define Texture_hpp

#include "Commons.hpp"

#include <SDL2/SDL.h>

#include "vec2.hpp"

class Texture
{
public:
    
    Texture();
    Texture(const std::string& pPath);
    Texture(const int pZOrder, const std::string& pPath);
    Texture(const int pScreenX, const int pScreenY, const std::string& pPath);
    Texture(const int pScreenX, const int pScreenY, const int pZOrder, const std::string& pPath);
    virtual ~Texture();
    
    void init(
               const int pScreenX, const int pScreenY,
               const int pZOrder, const float pRotationDegree,
               const std::string& pPath
              );
    
    int getId() const;
    int getZOrder() const;
    
    void setWidth(const int pWidth);
    void setHeight(const int pHeight);
    int getWidth();
    int getHeight();
    
    virtual int getImagePosX() const;
    virtual int getImagePosY() const;
    int getScreenPosX();
    int getScreenPosY();
    glm::ivec2 getPosition() const;
    void setPosition(const glm::vec2& pos);
    
    void setRotation(const float pRotAngle);
    float getRotation() const;
    
    SDL_Texture* getTexture();
    
    bool loadImage();
    
    // Relise the sources
    void freeSelf();
    
    void updateScreenPos(const int pX, const int pY);
    
protected:
    
    int mId;
    int mZOrder;
    
    int mWidth;
    int mHeight;
    
    // In degrees
    float mRotationAngle;
    
    glm::ivec2 mPosition;
    
    std::string mPath;

    SDL_Texture* mTexture;
    
};

#endif /* Texture_hpp */
