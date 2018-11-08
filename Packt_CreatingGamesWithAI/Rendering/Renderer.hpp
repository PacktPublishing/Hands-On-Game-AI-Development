//
//  Renderer.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 06/12/2017.
//  Copyright © 2017 Cihan Ozer. All rights reserved.
//

//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                  //
//  Renderer encapsulates SDL and provides rendering operations for the application. render()       //
//  is called by ApplicationWindow.callOnFrame() on each frame and draw the current frame via SDL.  //
//                                                                                                  //
//  Renderer class is currently unstable.                                                           //
//                                                                                                  //
//////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef Renderer_hpp
#define Renderer_hpp

#include "Texture.hpp"
#include "RenderingBuffer.hpp"

#include <vector>

class Renderer
{
public:
    
    Renderer() {}
    Renderer(RenderingBuffer* buffer);
    ~Renderer();
    
    bool init(  const std::string& pTitle, const int pXpos, const int pYpos,
                  const int pWidth, const int pHeight, const Uint32 pSdlFlag);
    
    void reset();
    
    void setBuffer(RenderingBuffer* buffer);

    void callPreRender()    {}
    void render();
    void callPostRender();
    
    void freeSelf();
    
    SDL_Renderer* getSDLRenderer();
    
private:
    
    RenderingBuffer* mBufferPtr;
    
    // The window of the application
    SDL_Window* mSdlWindow;
    
    // The SDL renderer
    SDL_Renderer* mSdlRenderer;
    
    // The surface that we will render on
    SDL_Surface* mSdlScreenSurface;
};

#endif /* Renderer_hpp */
