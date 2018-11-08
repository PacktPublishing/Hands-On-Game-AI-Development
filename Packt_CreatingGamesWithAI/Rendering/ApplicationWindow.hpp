//
//  ApplicationWindow.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 06/12/2017.
//  Copyright © 2017 Cihan Ozer. All rights reserved.
//

//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                  //
//  ApplicationWindow provides an interface between SDL and the application's itself. callOnFrame() //
//  methods is called every frame and refreshes (draws, renders, etc.) the application screen for   //
//  the frame. Renderer object is used to handle this rendering operations. Each application has a  //
//  window to run.                                                                                  //
//                                                                                                  //
//////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef ApplicationWindow_hpp
#define ApplicationWindow_hpp

#include "TextureManager.hpp"
#include "Renderer.hpp"

class ApplicationWindow
{
public:
    
    ApplicationWindow();
    ~ApplicationWindow();
    
    void reset();
    
    // TODO Add some default values
    bool init(  const std::string& pTitle, const int pXpos, const int pYpos,
                const int pWidth, const int pHeight, const Uint32 pSdlFlag, const std::string& pPath,
                const SDL_Color& pBackGround
              );
    
    void pushTextures(std::vector<Texture*>& pTextures);
    void callOnFrame();
    
    bool close();
    
private:
    
    void sendToBuffer();
    
    SDL_Color mBackGroundColor;
    
    TextureManager mTextureManager;
    RenderingBuffer mBuffer;
    
    // Encapsulates SDL
    std::unique_ptr<Renderer> mRenderer;
};

#endif /* ApplicationWindow_hpp */
