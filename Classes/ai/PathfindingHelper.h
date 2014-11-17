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
#include "floodfill.h"


class LevelScene;

class PathfindingHelper : public cocos2d::Ref
{
public:
    static PathfindingHelper *getInstance();
    
    static void destroy();
    
    void setup(LevelScene* level) { _mLevel = level; };
    
    static vector<cocos2d::Point> startAStarSearch(const cocos2d::Point &start, const cocos2d::Point &goal);
    
    vector<cocos2d::Point> startFloodFill(const cocos2d::Point &coord, unsigned limited);
    
    
    
protected:
    PathfindingHelper(){};
    ~PathfindingHelper(){};
    
    LevelScene* _mLevel;
    
    
    friend class MapSearchNode;
};


class MapSearchNode
{
public:
    int x;	 // the (x,y) positions of the node in map.
    int y;   // aka tile coordinate
    
    MapSearchNode() { x = y = 0; }
    MapSearchNode( int px, int py ) { x=px; y=py; }
    MapSearchNode( const cocos2d::Point &p ) { x=p.x; y=p.y; }
    
    // implement pure virtual methods of AStarState
    float GoalDistanceEstimate( MapSearchNode &nodeGoal );
    bool IsGoal( MapSearchNode &nodeGoal );
    bool GetSuccessors( AStarSearch<MapSearchNode> *astarsearch, MapSearchNode *parent_node );
    float GetCost( MapSearchNode &successor );
    bool IsSameState( MapSearchNode &rhs );
    
    void PrintNodeInfo();
    
public: // for flood fill
    bool isValid();
};

#endif /* defined(__SanGuoYingJie__PathfindingHelper__) */
