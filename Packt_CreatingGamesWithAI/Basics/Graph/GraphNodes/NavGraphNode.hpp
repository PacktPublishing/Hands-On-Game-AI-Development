//
//  NavGraphNode.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 08/10/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#ifndef NavGraphNode_hpp
#define NavGraphNode_hpp

#include "GraphNode.hpp"

#include "vec2.hpp"

// Navigation graphs use navigation graph nodes. Navigation graph nodes are
// graphs nodes with position information and a void pointer that can be used
// to store any extra information, such as health pack, ammo chest, and so on.
template <class ExtraInfo = void*>
class NavGraphNode : public GraphNode
{
public:
    
    NavGraphNode()
        : GraphNode(), mExtraInfo( ExtraInfo() )
    { }
    
    NavGraphNode(const int pIndex, const glm::vec2& pPos)
        : GraphNode(pIndex), mPosition(pPos), mExtraInfo( ExtraInfo() )
    { }
    
    virtual ~NavGraphNode() { }
    
    glm::vec2 getPosition() const { return mPosition; }
    ExtraInfo getExtraInfo() const { return mExtraInfo; }
    
    void setPosition(const glm::vec2& pPos) { mPosition = pPos; }
    void setExtraInfo(ExtraInfo pExtraInfo) { mExtraInfo = pExtraInfo; }
    
private:
    
    glm::vec2 mPosition;
    ExtraInfo mExtraInfo;
    
};

#endif /* NavGraphNode_hpp */
