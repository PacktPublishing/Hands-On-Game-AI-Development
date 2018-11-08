//
//  Renderer.cpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 06/12/2017.
//  Copyright © 2017 Cihan Ozer. All rights reserved.
//

#include "Renderer.hpp"

#include <SDL2_image/SDL_image.h>

///////////// CONSTRUCTOR - DESTRUCTOR /////////////

Renderer::Renderer(RenderingBuffer* buffer)
{
    setBuffer(buffer);
}

Renderer::~Renderer()
{
    freeSelf();
}

///////////// PUBLIC METHODS /////////////

void Renderer::reset()
{
    
}

void Renderer::setBuffer(RenderingBuffer* buffer)
{
    mBufferPtr = buffer;
}

bool Renderer::init(const std::string &pTitle, const int pXpos, const int pYpos, const int pWidth, const int pHeight, const Uint32 pSdlFlag)
{
    bool isReady = false;
    if( SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1") )
    {
        mSdlWindow = SDL_CreateWindow(pTitle.c_str(), pXpos, pYpos, pWidth, pHeight, pSdlFlag);
        if(mSdlWindow != NULL)
        {
            // Create renderer for the window
            mSdlRenderer = SDL_CreateRenderer(mSdlWindow, -1, SDL_RENDERER_ACCELERATED);
            if(mSdlRenderer != NULL)
            {
                // Init renderer color
                SDL_SetRenderDrawColor(mSdlRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                
                // TODO move this to the TextureManager
                // Init PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( (IMG_Init(imgFlags) & imgFlags) )
                {
                    //Get window surface
                    mSdlScreenSurface = SDL_GetWindowSurface( mSdlWindow );
                    
                    isReady = true;
                }
                else
                {
                    printf( "SDL_image ERROR: %s\n", IMG_GetError() );
                }
            }
            else
            {
                printf( "Renderer could not be created! SDL_Error: %s\n", SDL_GetError() );
            }
        }
        else
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        }
    }
    else
    {
        printf( "NO inear filter texturing..." );
    }

    return isReady;
}

void Renderer::freeSelf()
{
    //Destroy window
    SDL_DestroyWindow( mSdlWindow );
    mSdlWindow = NULL;
    
    // Destroy renderer
    SDL_DestroyRenderer(mSdlRenderer);
    mSdlRenderer = NULL;
    
    // TODO Move to TextureManager?
    IMG_Quit();
}

void Renderer::render()
{
    // Clear
    SDL_SetRenderDrawColor(
                            mSdlRenderer, mBufferPtr->backGroundColor.r,
                            mBufferPtr->backGroundColor.g,
                            mBufferPtr->backGroundColor.b,
                            mBufferPtr->backGroundColor.a
                           );
    SDL_RenderClear(mSdlRenderer);

    // Render the texture
    for(const auto& texture : mBufferPtr->textureList)
    {
        SDL_Rect srcRect;
        SDL_Rect destRect;
        
        srcRect.x = texture->getImagePosX();
        srcRect.y = texture->getImagePosY();
        srcRect.w = destRect.w = texture->getWidth();
        srcRect.h = destRect.h = texture->getHeight();
        destRect.x = texture->getScreenPosX();
        destRect.y = texture->getScreenPosY();
        
        SDL_RenderCopyEx(mSdlRenderer, texture->getTexture(), &srcRect, &destRect, texture->getRotation(), 0, SDL_FLIP_NONE);
    }
    
    // Update the screen
    SDL_RenderPresent(mSdlRenderer);
}

void Renderer::callPostRender()
{

}

SDL_Renderer* Renderer::getSDLRenderer()
{
    return mSdlRenderer;
}

///////////// PRIVATE METHODS /////////////

