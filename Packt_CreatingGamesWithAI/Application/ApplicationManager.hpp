//
//  ApplicationManager.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 06/12/2017.
//  Copyright © 2017 Cihan Ozer. All rights reserved.
//

//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                  //
//  ApplicationManager controls the application(s) that will run. It manages the initializations    //
//  (SDL and the application(s) related), starts the executions, release the sources and end the    //
//  executions when it is needed. "Game loop" is also included to ApplicationManager and it calls   //
//  update() methods of the Applications (in startExecution() method).                              //
//                                                                                                  //
//////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef ApplicationManager_hpp
#define ApplicationManager_hpp

#include "Observer.hpp"

#include "Application.hpp"

#include <vector>

class ApplicationManager : public Observer
{
public:
    
    static ApplicationManager& getInstance();

    void startExecution();
    
private:
    
    ApplicationManager();
    ~ApplicationManager();
    
    void actionEventCallback(ActionEvent pEvent);
    void keyboardEventCallback(KeyboardEvents pEvent);
    
    bool init();

    bool close();
    
    int mNumOfDoneExes;
    
    std::vector< std::unique_ptr<Application> > mApplicationList;
    
};

#endif /* ApplicationManager_hpp */
