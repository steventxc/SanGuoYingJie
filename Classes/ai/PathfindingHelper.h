//
//  PathfindingHelper.h
//  SanGuoYingJie
//
//  Created by Steven.Xc.Tian.
//
//

#ifndef __SanGuoYingJie__PathfindingHelper__
#define __SanGuoYingJie__PathfindingHelper__

#include "cocos2d.h"
#include "stlastar.h"

class PathfindingHelper : public cocos2d::Ref
{
public:
    static PathfindingHelper *getInstance();
    
    void startAStarSearch(const cocos2d::Point &start, const cocos2d::Point &goal);
    
protected:
    PathfindingHelper();
    ~PathfindingHelper();
    
};


class MapSearchNode
{
public:
    int x;	 // the (x,y) positions of the node in map.
    int y;   // aka tile coordinate
    
    MapSearchNode() { x = y = 0; }
    MapSearchNode( int px, int py ) { x=px; y=py; }
    
    // implement pure virtual methods of AStarState
    float GoalDistanceEstimate( MapSearchNode &nodeGoal );
    bool IsGoal( MapSearchNode &nodeGoal );
    bool GetSuccessors( AStarSearch<MapSearchNode> *astarsearch, MapSearchNode *parent_node );
    float GetCost( MapSearchNode &successor );
    bool IsSameState( MapSearchNode &rhs );
    
    void PrintNodeInfo(); 
    
    
};

#endif /* defined(__SanGuoYingJie__PathfindingHelper__) */
