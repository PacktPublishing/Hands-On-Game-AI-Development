//
//  GraphNode.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 08/10/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#ifndef GraphNode_hpp
#define GraphNode_hpp

// Base graph node class having only a graph index
class GraphNode
{
public:

    GraphNode();
    GraphNode(const int pIndex);
    virtual ~GraphNode();
    
    int getIndex() const;
    void setIndex(const int pIndex);
    
protected:
    
    int mIndex;
};

#endif /* GraphNode_hpp */
