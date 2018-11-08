//
//  Object.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 07/03/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#ifndef Object_hpp
#define Object_hpp

// The very base class
class Object
{
public:
    
    Object();
    virtual ~Object();
    
    unsigned int getId();
    
private:
    
    unsigned int mId;
};

#endif /* Object_hpp */
