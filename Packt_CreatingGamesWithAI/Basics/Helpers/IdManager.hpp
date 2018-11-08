//
//  IdManager.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 07/03/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#ifndef IdManager_hpp
#define IdManager_hpp

#include <queue>

#define ID_Manager IdManager::getInstance()

// Helper class for managing given IDs
class IdManager
{
public:
    
    static IdManager& getInstance();
    void clear();
    
    unsigned int getNextId();
    void giveIdBack(const unsigned int pUsedId);
    
private:
    
    IdManager();
    ~IdManager();
    
    unsigned int mId;
    std::queue<unsigned int> mAvailableIds;
};


#endif /* IdManager_hpp */
