//
//  GameObject.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 07/03/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#ifndef GameObject_hpp
#define GameObject_hpp

#include "Object.hpp"

#include "IEventCallbacks.hpp"

// Base class for game related classes (at least at the meoment)
class GameObject //: public Object
{
public:
    
    GameObject();
    virtual ~GameObject();
};

#endif /* GameObject_hpp */
