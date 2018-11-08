//
//  ApplicationWindow.cpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 06/12/2017.
//  Copyright © 2017 Cihan Ozer. All rights reserved.
//

#include "ApplicationWindow.hpp"

#include "TextureLoader.hpp"

#include "RenderingBuffer.hpp"
#include "TextureManager.hpp"


///////////// CONSTRUCTOR - DESTRUCTOR /////////////

ApplicationWindow::ApplicationWindow()
{

}

ApplicationWindow::~ApplicationWindow()
{

}

///////////// PUBLIC METHODS /////////////

void ApplicationWindow::reset()
{
    mBuffer.clear();
    mTextureManager.reset();
    mRenderer->reset();
}

bool ApplicationWindow::init(
                                const std::string &pTitle, const int pXpos, const int pYpos,
                                const int pWidth, const int pHeight, const Uint32 pSdlFlag,
                                const std::string& pPath, const SDL_Color& pBackGround
                             )
{
    mBackGroundColor.r = pBackGround.r;
    mBackGroundColor.g = pBackGround.g;
    mBackGroundColor.b = pBackGround.b;
    mBackGroundColor.a = pBackGround.a;
    
    mRenderer = std::make_unique<Renderer>(&mBuffer);
    auto result = mRenderer->init(pTitle, pXpos, pYpos, pWidth, pHeight, pSdlFlag);
    if(result)
    {
        TextureLoader::setSdlRenderer( mRenderer->getSDLRenderer() );
    }
    return result;
    
}

void ApplicationWindow::pushTextures(std::vector<Texture*>& pTextures)
{
    mTextureManager.prepareTextures(pTextures);
}

void ApplicationWindow::callOnFrame()
{
    // Render the current frame
    sendToBuffer();
    mRenderer->render();
}

bool ApplicationWindow::close()
{
    mRenderer->freeSelf();
    
    return true;
}

void ApplicationWindow::sendToBuffer()
{
    mBuffer.clear();
    
    mBuffer.backGroundColor = mBackGroundColor;
    mTextureManager.pushTexturesToBuffer(mBuffer.textureList);
}
