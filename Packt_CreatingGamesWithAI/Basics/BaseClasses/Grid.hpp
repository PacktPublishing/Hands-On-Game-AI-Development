//
//  Grid.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 19/06/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#ifndef Grid_hpp
#define Grid_hpp

#include <vector>
#include <cmath>

// Base Grid class for any grid related usage
template <class entity_type>
class Grid
{
public:
    
    Grid(const int pWidth, const int pHeight, const int pCellSize)
    : mWidth(pWidth), mHeight(pHeight), mCellSize(pCellSize)
    {
        mGrids = std::vector<std::vector<std::vector<const entity_type*>>>(( (int)std::roundf((float)mHeight / mCellSize )));
        
        auto rowSize = mGrids.size();
        auto colSize = (int)std::roundf((float)mWidth / mCellSize);
        for (size_t row = 0; row < rowSize; row++)
        {
            for (int col = 0; col < colSize; col++)
            {
                mGrids[row].push_back(std::vector<const entity_type*>());
            }
        }
    }
    
    virtual ~Grid()
    {
        clear();
    }
    
    // Insert to the grid
    virtual void insert(const entity_type* obj) = 0;
    virtual void iterateGrid() = 0;
    
    // Clear the grid objects for the next frame
    void clear()
    {
        auto rowSize = mGrids.size();
        auto colSize = (int)std::roundf((float)mWidth / mCellSize);
        
        for (auto row = 0; row < rowSize; row++)
        {
            for (auto col = 0; col < colSize; col++)
            {
                mGrids[row][col].clear();
            }
        }
    }
    
    
protected:
    // TODO Maybe use an array?
    std::vector< std::vector< std::vector<const entity_type*> > > mGrids;
    
    int mWidth, mHeight;
    int mCellSize;
};



template <class entity_type>
class LegacyGrid
{
public:

    LegacyGrid(const int pWidth, const int pHeight, const int pCellSize)
        : mWidth(pWidth), mHeight(pHeight), mCellSize(pCellSize)
    {
        mGrids = std::vector<std::vector<std::vector<entity_type*>>>((mHeight / mCellSize));
        
        auto rowSize =  mGrids.size();
        auto colSize = mWidth / mCellSize;
        for (int row = 0; row < rowSize; row++)
        {
            for (int col = 0; col < colSize; col++)
            {
                mGrids[row].push_back(std::vector<entity_type*>());
            }
        }
    }
    virtual ~LegacyGrid()
    {
        clear();
    }
    
    // Insert rigid-body to the grid
    virtual void insert(entity_type* obj) = 0;
    virtual void iterateGrid() = 0;
    
    // Clear the grid objects for the next frame
    void clear()
    {
        auto rowSize =  mGrids.size();
        auto colSize = mWidth / mCellSize;
        
        for (auto row = 0; row < rowSize; row++)
        {
            for (auto col = 0; col < colSize; col++)
            {
                mGrids[row][col].clear();
            }
        }
    }
    
    
protected:
    
    std::vector< std::vector< std::vector<entity_type*> > > mGrids;
    
    int mWidth, mHeight;
    int mCellSize;
};


#endif /* Grid_hpp */
