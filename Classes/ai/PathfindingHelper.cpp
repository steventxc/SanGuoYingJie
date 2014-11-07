//
//  PathfindingHelper.cpp
//  SanGuoYingJie
//
//  Created by Steven.Xc.Tian.
//
//

#include "PathfindingHelper.h"
#include "../game/TKMap.h"
#include "../data/MapTerrain.h"

USING_NS_CC;

#define DEBUG_PATHFINDING   1


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

void PathfindingHelper:: destroy()
{
    CC_SAFE_DELETE(s_InstancePathfindingHelper);
}


vector<Point> PathfindingHelper:: startAStarSearch(const cocos2d::Point &start, const cocos2d::Point &goal)
{
    AStarSearch<MapSearchNode> astarsearch;
    
    
    // Create a start state
    MapSearchNode nodeStart(start);
    
    // Define the goal state
    MapSearchNode nodeEnd(goal);
    
    // Set Start and goal states
    astarsearch.SetStartAndGoalStates( nodeStart, nodeEnd );
    
    unsigned int SearchState;
    unsigned int SearchSteps = 0;
    
    do
    {
        SearchState = astarsearch.SearchStep();
        
        SearchSteps++;
    }
    while( SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_SEARCHING );
    
    if( SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_SUCCEEDED )
    {
        CCLOG("Search found goal state\n");
        
        vector<Point> _solution;
        
        MapSearchNode *node = astarsearch.GetSolutionStart();
        
        
        int steps = 0;
        
        // add start point.
        _solution.push_back(Point(node->x, node->y));
        node->PrintNodeInfo();
        for( ;; )
        {
            node = astarsearch.GetSolutionNext();
            
            if( !node )
            {
                break;
            }
            
            _solution.push_back(Point(node->x, node->y));
            node->PrintNodeInfo();
            steps ++;
            
        };
#if DEBUG_PATHFINDING
        CCLOG("Solution steps %d", steps);
#endif
        
        // Once you're done with the solution you can free the nodes up
        astarsearch.FreeSolutionNodes();
        
        return _solution;
    }
    else if( SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_FAILED )
    {
        CCLOG("Search terminated. Did not find goal state\n");
    }
    
    // Display the number of loops the search went through
    //    CCLOG("SearchSteps : %d\n", SearchSteps);
    
    astarsearch.EnsureMemoryFreed();
	
    return vector<Point>();
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
#if DEBUG_PATHFINDING
    CCLOG("Node position : (%d,%d)", x,y);
#endif
}

/*
 * Here's the heuristic function that estimates the distance from a Node to the Goal.
 * Here use "Manhattan distance".
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
    Vec2 _point;
    auto _map = PathfindingHelper::getInstance()->_tkmap;
    
	// push each possible move except allowing the search to go backwards
    
    // left
    _point.set(x-1, y);
	if( !((parent_x == x-1) && (parent_y == y))
       && ( !_map->isObstacle(_point) )
       )
	{
		NewNode = MapSearchNode( _point );
		astarsearch->AddSuccessor( NewNode );
	}
    
    // top
    _point.set(x, y-1);
	if( !((parent_x == x) && (parent_y == y-1))
       && ( !_map->isObstacle(_point) )
       )
	{
		NewNode = MapSearchNode( _point );
		astarsearch->AddSuccessor( NewNode );
	}
    
    // right
    _point.set(x+1, y);
	if(!((parent_x == x+1) && (parent_y == y))
       && ( !_map->isObstacle(_point) )
       )
	{
		NewNode = MapSearchNode( _point );
		astarsearch->AddSuccessor( NewNode );
	}
    
    // bottom
    _point.set(x, y+1);
	if( !((parent_x == x) && (parent_y == y+1))
       && ( !_map->isObstacle(_point) )
       )
	{
		NewNode = MapSearchNode( _point );
		astarsearch->AddSuccessor( NewNode );
	}
    
    return true;
}

// given this node, what does it cost to move to successor. In the case
// of our map the answer is the map terrain value at this node since that is
// conceptually where we're moving

float MapSearchNode::GetCost( MapSearchNode &successor )
{
    int gid = PathfindingHelper::getInstance()->_tkmap->getTileGID(Point(x, y));
    unsigned type = PathfindingHelper::getInstance()->_tkmap->getTileTerrain(gid);
    
    return MapTerrain::getTerrainCost(type);
}
