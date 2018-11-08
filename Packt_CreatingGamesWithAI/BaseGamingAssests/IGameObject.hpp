//
//  IGameObject.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 22/09/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#ifndef IGameObject_hpp
#define IGameObject_hpp

#include "Texture.hpp"

// Interface that declares the necessary abstract methods for a GameObject
class IGameObject
{
public:
    
    // "A base class destructor should be either public and virtual, or protected and nonvirtual."
    // Herb Sutter, Guru of the Week #18: "Virtuality"
    //
    // If there are virtual functions, there needs to be a virtual destructor. Always. It does
    // not matter that it's only an interface class - it still needs the virtual destructor.
    //
    // Either that, or it needs a protected nonvirtual destructor. But then you cannot delete
    // the object using the interface pointer.
    virtual ~IGameObject() { }
    
    // Initialize the object. Run the code depends on other objects here
    void initObject(const int pArgNumber, ...)
    {
        va_list args;
        va_start(args, pArgNumber);
        performInit(pArgNumber, args);
        va_end(args);
    }
    
    virtual void reset(){ }
    
    // Frame methods: pre-frame, on-frame, and post-frame
    // !!! WARNING !!! //
    //
    // THESE METHODS ARE STILL UNSTABLE. THEIR EXACT DESTINY SHALL BE
    // DECIDED IN THE NEAR FUTURE
    //
    // !!! WARNING !!! //
    virtual void callPreFrame() { }
    virtual void callOnFrame() { }
    virtual void callPostFrame() { }
    
    // Rendering methods: pre-render, on-render, and post-render
    // !!! WARNING !!! //
    //
    // THESE METHODS ARE STILL UNSTABLE. THEIR EXACT DESTINY SHALL BE
    // DECIDED IN THE NEAR FUTURE
    //
    // !!! WARNING !!! //
    // Push your textures to the buffer
    virtual void callOnRender(std::vector<Texture*>& mTextures) { }
    
private:
    
    virtual void performInit(const int pArgNumber, va_list args) { }
};

#endif /* IGameObject_hpp */
