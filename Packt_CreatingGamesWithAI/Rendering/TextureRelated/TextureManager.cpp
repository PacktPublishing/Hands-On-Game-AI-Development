//
//  TextureManager.cpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 07/05/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#include "TextureManager.hpp"

#include <SDL2_image/SDL_image.h>

struct
{
    bool operator()(Texture* first, Texture* second) const
    {
        return first->getZOrder() < second->getZOrder();
    }
    
} zComparer;

///////////// CONSTRUCTOR - DESTRUCTOR /////////////

TextureManager::TextureManager()
{
    
}

TextureManager::~TextureManager()
{
    freeSelf();
}

void TextureManager::freeSelf()
{
    reset();
}

///////////// PUBLIC METHODS /////////////

void TextureManager::reset()
{
    mTextureList.clear();
}

void TextureManager::prepareTextures(std::vector<Texture*>& pTextureList)
{
    mTextureList.clear();
    for(const auto& texture : pTextureList)
    {
        if(texture->getTexture() != nullptr)
        {
            mTextureList.push_back(texture);
        }
    }
    
    std::sort(mTextureList.begin(), mTextureList.end(), zComparer);
}

void TextureManager::pushTexturesToBuffer(std::vector<Texture*>& bufferList)
{
    bufferList = mTextureList;
}
