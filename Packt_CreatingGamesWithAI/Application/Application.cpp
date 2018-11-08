//
//  Application.cpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 14/12/2017.
//  Copyright © 2017 Cihan Ozer. All rights reserved.
//

#include "Application.hpp"

#include "ApplicationInputManager.hpp"

Application::Application()
{
    AppInputManager.addSdlinatorCallback(this, &Application::actionEventCallback);
    AppInputManager.addKeyboardCallback(this, &Application::keyboardEventCallback);
    AppInputManager.addMouseCallback(this, &Application::mouseEventCallback);
}

Application::~Application()
{

}
