//
//  Application.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 06/12/2017.
//  Copyright © 2017 Cihan Ozer. All rights reserved.
//

#ifndef Application_hpp
#define Application_hpp

#include "Commons.hpp"

#include "Observer.hpp"

#include "ApplicationWindow.hpp"

class Application : public Observer
{
public:
    
    Application();
    
    virtual ~Application();
    
    int getWindowPosX()
    {
        return mWindowPosX;
    }
    
    int getWindowPosY()
    {
        return mWindowPosY;
    }
    
    int getWindowWidth()
    {
        return mWindowWidth;
    }
    
    int getWindoweight()
    {
        return mWindowHeight;
    }
    
    std::string getWindowTitle()
    {
        return mTitle;
    }
    
    std::string getImagePath()
    {
        return mImagePath;
    }
    
    virtual void reset()    {   }
    
    virtual void update() = 0;
    
    
protected:
    
    virtual bool init() = 0;
    
    bool mIsReadyToRun;
    bool mIsQuit;
    
    int mWindowPosX, mWindowPosY;
    int mWindowWidth, mWindowHeight;
    
    std::string mTitle;
    std::string mImagePath;
    
    std::unique_ptr<ApplicationWindow> mWindow;
    
};

#endif /* Application_hpp */
