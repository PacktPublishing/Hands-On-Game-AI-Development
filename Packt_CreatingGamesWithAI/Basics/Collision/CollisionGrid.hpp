//
//  CollisionGrid.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 19/06/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#ifndef CollisionGrid_hpp
#define CollisionGrid_hpp

#include "Grid.hpp"
#include "Collider.hpp"

// Uniform grid for collision detection.

// Scope of this project does not mind whether there is a brute-force or "smart" collising
// detection handling. But, it is good to have it before hand in case of number of rigid bodies will increase.

// Why uniform grid?
// BVH: We have many objects moving all around during the frames. Constructing BVH for each frame would be very costly.
// Spatial partitioning techniques are better and more suitable since our borders are exact and static. Thus, we can
// easily construct our hierarchy based on object positions for each frame really fast.

//BSP: Good for indoor games (such as Quake) and collision detections between level geometry and game level } This are
// not really the case for this game, so BSP is not suitable.

// Quadtree and Unifrom grid are very suitable of this game's design. However, uniform grid is easier to handle and construct
// than quadtree since all the rigid bodies we have move all around the screen (a "large open space").
class CollisionGrid : public Grid<Collider>
{
public:
    
    CollisionGrid(const int pWidth, const int pHeight, const int pCellSize)
        : Grid(pWidth, pHeight, pCellSize)
    { }
    
    virtual ~CollisionGrid() { }
    
    void insert(const Collider* obj) override
    {
        // This code inserts a single rigid body into multiple grids if necessary

        auto objMinPos = obj->getMinPos();
        auto objMaxPos = obj->getMaxPos();
        
        int startRow = std::max(0, (int)(objMinPos.y / mCellSize));
        int startCol = std::max(0, (int)(objMinPos.x / mCellSize));
        int endRow = std::min((int)mGrids.size() - 1, (int)(objMaxPos.y / mCellSize));
        int endCol = std::min((int)mGrids[0].size() - 1, (int)(objMaxPos.x / mCellSize));
        
        // Insert into the grids
        for (auto row = startRow; row <= endRow; row++)
        {
            for (auto col = startCol; col <= endCol; col++)
            {
                mGrids[row][col].push_back(obj);
            }
        }
    }
    
    void iterateGrid() override
    {
        // TODO Oh boy, this look horrifying!
        
        for (size_t row = 0; row < mGrids.size(); ++row)    // For each row of the grid
        {
            for (size_t col = 0; col < mGrids[row].size(); ++col)    // For each column of the grid
            {
                if (mGrids[row][col].size() > 1)    // If there is more than one object in the current cell of the grid
                {
                    for (size_t rbI = 0; rbI < mGrids[row][col].size(); ++rbI)    // Check collision for the objects
                    {
                        for (size_t rbII = rbI + 1; rbII < mGrids[row][col].size(); ++rbII)
                        {
                            if (mGrids[row][col].at(rbI)->checkCollision(mGrids[row][col].at(rbII)))
                            {
                                // COLLISION IS HAPPENING
                                mGrids[row][col].at(rbI)->collide(mGrids[row][col].at(rbII));
                                mGrids[row][col].at(rbII)->collide(mGrids[row][col].at(rbI));
                            }
                        }
                    }
                }
            }
        }
    }
    
    // Returns true if the given point collides with an object in the collision grid
    // Returns false otherwise
    bool queryPoint(const glm::vec2& pPoint) const
    {
        // Calculate indicies
        int startRow = std::max(0, (int)(pPoint.y / mCellSize));
        int startCol = std::max(0, (int)(pPoint.x / mCellSize));
        int endRow = std::min((int)mGrids.size() - 1, (int)(pPoint.y / mCellSize));
        int endCol = std::min((int)mGrids[0].size() - 1, (int)(pPoint.x / mCellSize));
        
        // Query the point
        for (auto row = startRow; row <= endRow; row++)
        {
            for (auto col = startCol; col <= endCol; col++)
            {
                if (mGrids[row][col].size() > 0)    // If there is more than one object in the current cell of the grid
                {
                    for (size_t rbI = 0; rbI < mGrids[row][col].size(); ++rbI)    // Check collision for the objects
                    {
                        if( mGrids[row][col].at(rbI)->checkCollision(pPoint) )
                        {
                            return true;
                        }
                    }
                }
            }
        }
        
        return false;
    }
    
    // Returns true if the given collider collides with an object in the collision grid
    // Returns false otherwise
    bool querryCollider(const Collider* collider) const
    {
        auto objMinPos = collider->getMinPos();
        auto objMaxPos = collider->getMaxPos();
        
        int startRow = std::max(0, (int)(objMinPos.y / mCellSize));
        int startCol = std::max(0, (int)(objMinPos.x / mCellSize));
        int endRow = std::min((int)mGrids.size() - 1, (int)(objMaxPos.y / mCellSize));
        int endCol = std::min((int)mGrids[0].size() - 1, (int)(objMaxPos.x / mCellSize));
        
        // Query the collider
        for (auto row = startRow; row <= endRow; row++)
        {
            for (auto col = startCol; col <= endCol; col++)
            {
                if (mGrids[row][col].size() > 0)    // If there is more than one object in the current cell of the grid
                {
                    for (size_t rbI = 0; rbI < mGrids[row][col].size(); ++rbI)    // Check collision for the objects
                    {
                        if( mGrids[row][col].at(rbI)->checkCollision(collider) )
                        {
                            return true;
                        }
                    }
                }
            }
        }
        
        return false;
    }
};

template <typename ColliderType>
class LegacyCollisionGrid : public LegacyGrid<LegacyCollider>
{
public:
    
    typedef LegacyGrid<LegacyCollider> CollidingGrid;
    
    LegacyCollisionGrid(const int pWidth, const int pHeight, const int pCellSize)
        : CollidingGrid::LegacyGrid(pWidth, pHeight, pCellSize)
    {}

    ~LegacyCollisionGrid()
    {}
    
    void insert(LegacyCollider* obj)
    {
        // This code inserts a single rigid body into multiple grids if necessary
        
        int startRow = std::max(0, (int)(obj->getBboxTopLeft().y / CollidingGrid::mCellSize));
        int startCol = std::max(0, (int)(obj->getBboxTopLeft().x / CollidingGrid::mCellSize));
        int endRow = std::min((int)CollidingGrid::mGrids.size() - 1, (int)(obj->getBboxDownRight().y / CollidingGrid::mCellSize));
        int endCol = std::min((int)CollidingGrid::mGrids[0].size() - 1, (int)(obj->getBboxDownRight().x / CollidingGrid::mCellSize));

        // Insert into the grids
        for (auto row = startRow; row <= endRow; row++)
        {
            for (auto col = startCol; col <= endCol; col++)
            {
                CollidingGrid::mGrids[row][col].push_back(obj);
            }
        }
    }
    
    void iterateGrid()
    {
        // Keep id's of the collided objects } In this way, we can prevent multiple collision of
        // the same objects involving more than one grid cell
        
        for (int row = 0; row < CollidingGrid::mGrids.size(); row++)    // For each row of the grid
        {
            for (int col = 0; col < CollidingGrid::mGrids[row].size(); col++)    // For each column of the grid
            {
                if (CollidingGrid::mGrids[row][col].size() > 1)    // If there is more than one object in the current cell of the grid
                {
                    for (int rbI = 0; rbI < CollidingGrid::mGrids[row][col].size(); rbI++)    // Check collision for the objects
                    {
                        for (int rbII = rbI + 1; rbII < CollidingGrid::mGrids[row][col].size(); rbII++)
                        {
                            if (CollidingGrid::mGrids[row][col].at(rbI)->checkCollision(CollidingGrid::mGrids[row][col].at(rbII)))
                            {
                                // COLLISION IS HAPPENING
                                CollidingGrid::mGrids[row][col].at(rbI)->collide(CollidingGrid::mGrids[row][col].at(rbII));
                                CollidingGrid::mGrids[row][col].at(rbII)->collide(CollidingGrid::mGrids[row][col].at(rbI));
                            }
                        }
                    }
                }
            }
        }
    }
};

#endif /* CollisionGrid_hpp */
