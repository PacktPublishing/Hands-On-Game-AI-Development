//
//  Texture.cpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 18/12/2017.
//  Copyright © 2017 Cihan Ozer. All rights reserved.
//

#include "Texture.hpp"

#include "TextureLoader.hpp"    // For loading the textures

#include "IdManager.hpp"


///////////// CONSTRUCTOR - DESTRUCTOR /////////////

Texture::Texture()
    :   mId( ID_Manager.getNextId() ), mZOrder(TextureCommons::DEFAULT_Z_ORDER),
        mWidth(TextureCommons::DEFAULT_WIDTH), mHeight(TextureCommons::DEFAULT_HEIGHT),
        mRotationAngle(0.f), mPosition(TextureCommons::DEFAULT_POS_X, TextureCommons::DEFAULT_POS_Y),
        mPath(TextureCommons::DEFAULT_IMAGE_PATH), mTexture(NULL)
{
    loadImage();
}

Texture::Texture(const std::string& pPath)
    :   mId( ID_Manager.getNextId() ), mZOrder(TextureCommons::DEFAULT_Z_ORDER),
        mWidth(TextureCommons::DEFAULT_WIDTH), mHeight(TextureCommons::DEFAULT_HEIGHT),
        mRotationAngle(0.f), mPosition(TextureCommons::DEFAULT_POS_X, TextureCommons::DEFAULT_POS_Y),
        mPath(pPath), mTexture(NULL)
{
    loadImage();
}

Texture::Texture(const int pZOrder, const std::string& pPath)
    :   mId( ID_Manager.getNextId() ), mZOrder(pZOrder),
        mWidth(TextureCommons::DEFAULT_WIDTH), mHeight(TextureCommons::DEFAULT_HEIGHT),
        mRotationAngle(0.f), mPosition(TextureCommons::DEFAULT_POS_X, TextureCommons::DEFAULT_POS_Y),
        mPath(pPath), mTexture(NULL)
{
    loadImage();
}

Texture::Texture(const int pScreenX, const int pScreenY, const std::string& pPath)
    :   mId( ID_Manager.getNextId() ), mZOrder(TextureCommons::DEFAULT_Z_ORDER),
        mWidth(TextureCommons::DEFAULT_WIDTH), mHeight(TextureCommons::DEFAULT_HEIGHT),
        mRotationAngle(0.f), mPosition(pScreenX, pScreenY),
        mPath(pPath), mTexture(NULL)
{
    loadImage();
}

Texture::Texture(const int pScreenX, const int pScreenY, const int pZOrder, const std::string& pPath)
    :   mId( ID_Manager.getNextId() ), mZOrder(pZOrder),
        mWidth(TextureCommons::DEFAULT_WIDTH), mHeight(TextureCommons::DEFAULT_HEIGHT),
        mRotationAngle(0.f), mPosition(pScreenX, pScreenY),
        mPath(pPath), mTexture(NULL)
{
    loadImage();
}

Texture::~Texture()
{
    freeSelf();
}

void Texture::init(
                    const int pScreenX, const int pScreenY,
                    const int pZOrder, const float pRotationDegree,
                    const std::string& pPath
                   )
{
    mPosition.x = pScreenX;
    mPosition.y = pScreenY;
    mZOrder = pZOrder;
    
    mRotationAngle = pRotationDegree;
    
    mPath = pPath;
    
    loadImage();
}

///////////// SETTERS AND GETTERS /////////////

int Texture::getId() const { return mId; }
int Texture::getZOrder() const { return mZOrder; }

void Texture::setWidth(const int pWidth) {   mWidth = pWidth;   }
void Texture::setHeight(const int pHeight)  { mHeight = pHeight; }
int Texture::getWidth()     {   return mWidth;  }
int Texture::getHeight()    {   return mHeight; }

int Texture::getImagePosX() const{   return 0; }
int Texture::getImagePosY() const{   return 0; }

int Texture::getScreenPosX()    {   return mPosition.x; }
int Texture::getScreenPosY()    {   return mPosition.y; }
glm::ivec2 Texture::getPosition() const { return mPosition; }
void Texture::setPosition(const glm::vec2& pos) { mPosition = pos; }

void Texture::setRotation(const float pRotAngle) { mRotationAngle = pRotAngle; }
float Texture::getRotation() const { return mRotationAngle; }

//SDL_Rect* Texture::getImageRactangle()  {   return mRect;       }
SDL_Texture* Texture::getTexture()      {   return mTexture;    }

///////////// PUBLIC METHODS /////////////

//bool Texture::loadImage(const std::string &pPath, SDL_Renderer* pRenderer)
bool Texture::loadImage()
{
    mTexture = TextureLoader::loadTexture(mPath, mWidth, mHeight);

    return mTexture != NULL;
}

void Texture::freeSelf()
{
    ID_Manager.giveIdBack(mId);
    
    // If there is a texture to free...
    if(mTexture != NULL)
    {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
    }
    
    mWidth = 0;
    mHeight = 0;
    
    mPosition.x = 0;
    mPosition.y = 0;
}

///////////// PRIVATE METHODS /////////////


