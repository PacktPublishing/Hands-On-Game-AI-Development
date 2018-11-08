//
//  Commons.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 06/12/2017.
//  Copyright © 2017 Cihan Ozer. All rights reserved.
//

#ifndef Commons_hpp
#define Commons_hpp

#include <string>

namespace TextureCommons
{
    const int DEFAULT_Z_ORDER = 0;
    const int INVALID_TEXTURE_ID = -1;
    
    const int DEFAULT_POS_X = 0;
    const int DEFAULT_POS_Y = 0;
    
    const int DEFAULT_WIDTH = 128;
    const int DEFAULT_HEIGHT = 128;
    
    const std::string DEFAULT_IMAGE_PATH = "Images/Default/DEFAULT_IMAGE.jpg";
}

namespace MathCommons
{
    const float EPSILON = 0.000001f;
    
    extern bool approximatelyEqual(float a, float b);
    extern bool essentiallyEqual(float a, float b);
    extern bool definitelyGreaterThan(float a, float b);
    extern bool definitelyLessThan(float a, float b);
    
    extern unsigned int randomUint(unsigned int min, unsigned int max);
    extern int randomInt(int min, int max);
    extern float randomFloat(float a, float b);
    extern double randomDouble(double a, double b);
}

namespace GraphCommons
{
    const int INVALID_NODE_INDEX = -1;
    const float DEFAULT_COST = 1.f;
}

#endif /* Commons_hpp */
