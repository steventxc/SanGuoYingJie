//
//  PathfindingHelper.cpp
//  SanGuoYingJie
//
//  Created by Steven.Xc.Tian.
//
//

#include "PathfindingHelper.h"

USING_NS_CC;


// singleton stuff
static PathfindingHelper *s_InstancePathfindingHelper = nullptr;

PathfindingHelper * PathfindingHelper:: getInstance()
{
    if (!s_InstancePathfindingHelper)
    {
        s_InstancePathfindingHelper = new (std::nothrow) PathfindingHelper();
        CCASSERT(s_InstancePathfindingHelper, "FATAL: Not enough memory");
    }
    
    return s_InstancePathfindingHelper;
}

void PathfindingHelper:: startAStarSearch(const cocos2d::Point &start, const cocos2d::Point &goal)
{
    
}


PathfindingHelper::PathfindingHelper()
{
    
}

PathfindingHelper::~PathfindingHelper()
{
    
}


// =================================================


bool MapSearchNode::IsSameState( MapSearchNode &rhs )
{
    // same state in a maze search is simply when (x,y) are the same
    if( (x == rhs.x) && (y == rhs.y) )
    {
        return true;
    }
    else
    {
        return false;
    }
    
}

void MapSearchNode::PrintNodeInfo()
{
    CCLOG("Node position : (%d,%d)\n", x,y);
}

/*
 * Here's the heuristic function that estimates the distance from a Node to the Goal.
 *
 */
float MapSearchNode::GoalDistanceEstimate( MapSearchNode &nodeGoal )
{
    float xd = abs( (float)x - (float)nodeGoal.x );
    float yd = abs( (float)y - (float)nodeGoal.y );
    
    return xd + yd;
    
}

bool MapSearchNode::IsGoal( MapSearchNode &nodeGoal )
{
    
    if( (x == nodeGoal.x) && (y == nodeGoal.y) )
    {
        return true;
    }
    
    return false;
}

// This generates the successors to the given Node. It uses a helper function called
// AddSuccessor to give the successors to the AStar class. The A* specific initialisation
// is done for each node internally, so here you just set the state information that
// is specific to the application
bool MapSearchNode::GetSuccessors( AStarSearch<MapSearchNode> *astarsearch, MapSearchNode *parent_node )
{
    
    int parent_x = -1;
    int parent_y = -1;
    
    if( parent_node )
    {
        parent_x = parent_node->x;
        parent_y = parent_node->y;
    }
    
    
    MapSearchNode NewNode;
    
    // push each possible move except allowing the search to go backwards
    
    if( (GetMap( x-1, y ) < 9)
       && !((parent_x == x-1) && (parent_y == y))
       )
    {
        NewNode = MapSearchNode( x-1, y );
        astarsearch->AddSuccessor( NewNode );
    }
    
    if( (GetMap( x, y-1 ) < 9)
       && !((parent_x == x) && (parent_y == y-1))
       )
    {
        NewNode = MapSearchNode( x, y-1 );
        astarsearch->AddSuccessor( NewNode );
    }
    
    if( (GetMap( x+1, y ) < 9)
       && !((parent_x == x+1) && (parent_y == y))
       )
    {
        NewNode = MapSearchNode( x+1, y );
        astarsearch->AddSuccessor( NewNode );
    }
    
    
    if( (GetMap( x, y+1 ) < 9)
       && !((parent_x == x) && (parent_y == y+1))
       )
    {
        NewNode = MapSearchNode( x, y+1 );
        astarsearch->AddSuccessor( NewNode );
    }
    
    return true;
}

// given this node, what does it cost to move to successor. In the case
// of our map the answer is the map terrain value at this node since that is 
// conceptually where we're moving

float MapSearchNode::GetCost( MapSearchNode &successor )
{
    return (float) GetMap( x, y );
    
}
