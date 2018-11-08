//
//  Commons.cpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 06/12/2017.
//  Copyright © 2017 Cihan Ozer. All rights reserved.
//

#include "Commons.hpp"

#include <cmath>
#include <cstdlib>

namespace MathCommons
{
    // Knuth D.E. The art of computer programming, vol II, section 4.2,
    // especially Floating-Point Comparison 4.2.2, pages 198-220.
    //
    // Also: Boost library Floating-point Comparison page
    bool approximatelyEqual(float a, float b)
    {
        return std::fabsf(a - b) <= ( (std::fabsf(a) < std::fabsf(b) ? std::fabsf(b) : std::fabsf(a)) * std::numeric_limits<float>::epsilon() );
    }

    bool essentiallyEqual(float a, float b)
    {
        return std::fabsf(a - b) <= ( (std::fabsf(a) > std::fabsf(b) ? std::fabsf(b) : std::fabsf(a)) * std::numeric_limits<float>::epsilon());
    }

    bool definitelyGreaterThan(float a, float b)
    {
        return (a - b) > ( (std::fabsf(a) < std::fabsf(b) ? std::fabsf(b) :std::fabsf(a)) * std::numeric_limits<float>::epsilon());
    }

    bool definitelyLessThan(float a, float b)
    {
        return (b - a) > ( (std::fabsf(a) < std::fabsf(b) ? std::fabsf(b) : std::fabsf(a)) * std::numeric_limits<float>::epsilon() );
    }
    
    
    unsigned int randomUint(unsigned int min, unsigned int max)
    {
        if(min > max)
        {
            std::swap(min, max);
        }
        
        return min + ( std::rand() % (max - min + 1) );
    }
    
    // Max is inclusive
    int randomInt(int min, int max)
    {
        if(min > max)
        {
            std::swap(min, max);
        }
        
        return min + ( std::rand() % (max - min + 1) );
    }
    
    float randomFloat(float min, float max)
    {
        if(min > max)
        {
            std::swap(min, max);
        }
        
        // From: https://stackoverflow.com/questions/5289613/generate-random-float-between-two-floats
        auto random = ((float) rand()) / (float) RAND_MAX;
        return (random * (max - min) ) + min;
    }
    
    double randomDouble(double min, double max)
    {
        if(min > max)
        {
            std::swap(min, max);
        }
        
        // From: https://stackoverflow.com/questions/5289613/generate-random-float-between-two-floats
        auto random = ((double) rand()) / (double) RAND_MAX;
        return (random * (max - min) ) + min;
    }
}
