//
//  TextureLoader.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 14/05/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#ifndef TextureLoader_hpp
#define TextureLoader_hpp

#include <SDL2/SDL.h>

#include <string>

// TODO This breaks multiple windows support, but the current system of SDL texture loading
// seems like a killer anyway...
class TextureLoader
{
public:
    
    static void setSdlRenderer(SDL_Renderer* pRenderer);
    
    static SDL_Texture* loadTexture(std::string& pPath);
    static SDL_Texture* loadTexture(std::string& pPath, int& pWidth, int& pHeight);
    
private:
    
    static SDL_Renderer* mSdlRendererPtr;
};



#endif /* TextureLoader_hpp */
