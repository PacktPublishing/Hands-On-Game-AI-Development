//
//  RenderingBuffer.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 25/02/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#ifndef RenderingBuffer_hpp
#define RenderingBuffer_hpp

#include "Texture.hpp"

#include <SDL2/SDL.h>
#include <vector>

// A helper class for rendering.
// It acts as a buffer. The ApplicationWindow sets the related information
// into RenderingBuffer and Renderer gets this information and render the scene
class RenderingBuffer
{
public:
    
    RenderingBuffer();
    ~RenderingBuffer();
    
    void clear();
    
    SDL_Color backGroundColor;
    std::vector<Texture*> textureList;
    
private:
    
   
};

#endif /* RenderingBuffer_hpp */
