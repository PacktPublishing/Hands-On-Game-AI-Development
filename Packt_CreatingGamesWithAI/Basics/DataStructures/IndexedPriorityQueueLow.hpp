//
//  IndexedPriorityQueueLow.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 09/10/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#ifndef IndexedPriorityQueueLow_hpp
#define IndexedPriorityQueueLow_hpp

#include <vector>

// A two-way heap based indexed priority queue with lowest valued keys
template<class KeyType>
class IndexedPriorityQueueLow
{
public:

    IndexedPriorityQueueLow(std::vector<KeyType>& keys, int pMaxSize)
        : mKeys(keys), mMaxSize(pMaxSize), mSize(0)
    {
        mHeap.assign(pMaxSize + 1, 0);
        mInvHeap.assign(pMaxSize + 1, 0);
    }
    
    bool empty() const {return ( mSize == 0); }
    
    // New item is added to the end of the heap and reordered from the bottom up
    void insert(const int pItem)
    {
        assert(mSize + 1 <= mMaxSize);
        
        ++mSize;
        mHeap[mSize] = pItem;
        mInvHeap[pItem] = mSize;
        
        reorderUpwards(mSize);
    }

    // Min item is exchanged with the lowest one in the heap and then the heap
    // is reorder from the top down
    int pop()
    {
        swap(1, mSize);
        reorderDownwards(1, mSize - 1);
        return mHeap[mSize--];
    }
    
    void changePriority(const int pItem)
    {
        reorderUpwards( mInvHeap[pItem] );
    }
    
private:

    void swap(int a, int b)
    {
        auto temp = mHeap[a];
        mHeap[a] = mHeap[b];
        mHeap[b] = temp;
        
        // Update the handles too
        mInvHeap[ mHeap[a] ] = a;
        mInvHeap[ mHeap[b] ] = b;
    }
    
    void reorderUpwards(int pItem)
    {
        // Reorder until the heap is ordered
        while ( (pItem > 1) && (mKeys[ mHeap[ pItem / 2] ] > mKeys[ mHeap[pItem] ]) )
        {
            swap(pItem / 2, pItem);
            pItem /= 2;
        }
    }
    
    void reorderDownwards(int pItem, int pHeapSize)
    {
        // Reorder until the heap is ordered
        while (2 * pItem <= pHeapSize)
        {
            auto child = 2 * pItem;
            
            // Set child to smaller of pItem's two children
            if( (child < pHeapSize) &&  (mKeys[ mHeap[child] ] > mKeys[ mHeap[child + 1] ] ) )
            {
                ++child;
            }
            
            // If this pItem is larger than its child, swap
            if (mKeys[ mHeap[pItem] ] > mKeys[ mHeap[child] ])
            {
                swap(child, pItem);
                // Move down the tree
                pItem = child;
            }
            else
            {
                break;
            }
        }
    }
    
    int mSize, mMaxSize;
    
    std::vector<KeyType>& mKeys;
    
    std::vector<int> mHeap;
    std::vector<int> mInvHeap;
    
    
};

#endif /* IndexedPriorityQueueLow_hpp */
