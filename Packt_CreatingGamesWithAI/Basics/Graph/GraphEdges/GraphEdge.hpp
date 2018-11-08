//
//  GraphEdge.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 08/10/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#ifndef GraphEdge_hpp
#define GraphEdge_hpp

// Base graph edge with from and to indices, and edge cost
class GraphEdge
{
public:
    
    GraphEdge();
    GraphEdge(const int pFrom, const int pTo);
    GraphEdge(const int pFrom, const int pTo, const float pCost);
    virtual ~GraphEdge();
    
    int getFrom() const;
    int getTo() const;
    float getCost() const;
    
    void setFrom(const int pFrom);
    void setTo(const int pTo);
    void setCost(const float pCost);
    
    bool operator==(const GraphEdge& pOther) const;
    bool operator!=(const GraphEdge& pOther) const;
    
protected:
    
    int mFrom, mTo;
    float mCost;
};

#endif /* GraphEdge_hpp */
