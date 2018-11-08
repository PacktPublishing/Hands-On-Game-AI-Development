//
//  Object.cpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 07/03/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#include "Object.hpp"

#include "IdManager.hpp"

Object::Object()
{
    mId = ID_Manager.getNextId();
}

Object::~Object()
{
    ID_Manager.giveIdBack(mId);
}

unsigned int Object::getId()
{
    return mId;
}
