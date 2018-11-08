//
//  TextureLoader.cpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 14/05/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#include "TextureLoader.hpp"

#include <SDL2_image/SDL_image.h>   // For loading the textures

SDL_Renderer* TextureLoader::mSdlRendererPtr;

void TextureLoader::setSdlRenderer(SDL_Renderer* pRenderer)
{
    mSdlRendererPtr = pRenderer;
}

SDL_Texture* TextureLoader::loadTexture(std::string& pPath) //, int zOrder)
{
    SDL_Texture* newTexture = NULL;
    
    // Load image at the path
    SDL_Surface* loadedSurface = IMG_Load( pPath.c_str() );
    if(loadedSurface != NULL)
    {
        // Color key the image
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF) );
        
        // Create the texture
        newTexture = SDL_CreateTextureFromSurface(mSdlRendererPtr, loadedSurface);
        if(newTexture == NULL)
        {
            printf( "Unable to load image %s! SDL Error: %s\n", pPath.c_str(), SDL_GetError() );
        }
        
        SDL_FreeSurface(loadedSurface);
    }
    else
    {
        printf( "SDL_image ERROR: %s\n", IMG_GetError() );
    }
    
    return newTexture;
}

SDL_Texture* TextureLoader::loadTexture(std::string& pPath, int& pWidth, int& pHeight)
{
    SDL_Texture* newTexture = NULL;
    
    // Load image at the path
    SDL_Surface* loadedSurface = IMG_Load( pPath.c_str() );
    if(loadedSurface != NULL)
    {
        // Color key the image
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF) );
        
        // Create the texture
        newTexture = SDL_CreateTextureFromSurface(mSdlRendererPtr, loadedSurface);
        if(newTexture == NULL)
        {
            printf( "Unable to load image %s! SDL Error: %s\n", pPath.c_str(), SDL_GetError() );
        }
        
        pWidth = loadedSurface->w;
        pHeight = loadedSurface->h;
        
        SDL_FreeSurface(loadedSurface);
    }
    else
    {
        printf( "SDL_image ERROR: %s\n", IMG_GetError() );
    }
    
    return newTexture;
}
