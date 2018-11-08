//
//  IdManager.cpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 07/03/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#include "IdManager.hpp"

IdManager::IdManager()
{
    mId = 0;
}

IdManager& IdManager::getInstance()
{
    static IdManager instance;
    return instance;
}

IdManager::~IdManager()
{
    clear();
}

void IdManager::clear()
{
    std::queue<unsigned int> empty;
    std::swap( mAvailableIds, empty );
}

unsigned int IdManager::getNextId()
{
    auto nextId = mId;
    if( !mAvailableIds.empty() )
    {
        nextId = mAvailableIds.front();
        mAvailableIds.pop();
    }
    else
    {
        mId++;
    }
    return nextId;
}

void IdManager::giveIdBack(const unsigned int pUsedId)
{
    mAvailableIds.push(pUsedId);
}
