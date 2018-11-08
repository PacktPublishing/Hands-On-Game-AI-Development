//
//  Timer.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 23/05/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#ifndef Timer_hpp
#define Timer_hpp

#include <SDL2/SDL_stdinc.h>

#include <chrono>

#define Time Timer::getInstance()

class Timer
{
public:

    static Timer& getInstance();
    
    float deltaTime;
    float time;
    void update();
    
    // Methods to control the timer
    void start();
    void stop();
    
    //Checks the status of the timer
    bool isStarted();
    
private:
    
    Timer();
    
    std::chrono::steady_clock::time_point mLastUpdate;
    
    bool mStarted;
};

#endif /* Timer_hpp */
