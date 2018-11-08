//
//  Timer.cpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 23/05/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#include "Timer.hpp"

#include <SDL2/SDL_timer.h>

#include <iostream>

#ifndef MAX
#define MAX(x,y) (((x) < (y)) ? (y) : (x))
#endif

Timer& Timer::getInstance()
{
    static Timer instance;
    return instance;
}

Timer::Timer()
{
    time = 0.f;
}

void Timer::update()
{
    // Delta time in seconds
    auto now = std::chrono::steady_clock::now();
    deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(now - mLastUpdate).count() / 1000000.0f;
    mLastUpdate = now;
    deltaTime = MAX(0, deltaTime);
    
//    if(deltaTime < 0.0166f)
//    {
//        deltaTime = 0.0166;
//    }
    
#if DEBUG
    // For preventing big delta time while debugging
    if (deltaTime > 0.2f)
    {
        deltaTime = 1 / 60.0f;
    }
#endif
    
    time += deltaTime;
}

void Timer::start()
{
    //Start the timer
    mStarted = true;
    
    //Get the current clock time
    mLastUpdate = std::chrono::steady_clock::now();
}

void Timer::stop()
{
    //Stop the timer
    mStarted = false;
}

bool Timer::isStarted()
{
    //Timer is running and paused or unpaused
    return mStarted;
}
