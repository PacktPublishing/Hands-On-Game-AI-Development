//
//  TextureManager.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 07/05/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#ifndef TextureManager_hpp
#define TextureManager_hpp

// Singleton TextureManager class. It loads, keeps, manages the the images,
// and works as a helper class for the rendering process.

#include "Texture.hpp"

#include <vector>
#include <map>

//struct TextureInfoBundle
//{
//    int screenX, screenY;
//    int zOrder;
//    std::string path;
//};

class TextureManager
{
public:
    
    TextureManager();
    ~TextureManager();
    void freeSelf();
    
    // TODO Not so sure whether I need this anymore
    void reset();
    
    void prepareTextures(std::vector<Texture*>& pTextureList);
    void pushTexturesToBuffer(std::vector<Texture*>& bufferList);
    
private:
   
    std::vector<Texture*> mTextureList;
    
};

#endif /* TextureManager_hpp */
