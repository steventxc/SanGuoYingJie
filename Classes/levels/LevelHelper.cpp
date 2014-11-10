//
//  LevelHelper.cpp
//  SanGuoYingJie
//
//  Created by Steven.Xc.Tian.
//
//

#include "LevelHelper.h"
#include "LevelScene.h"
#include "../game/Roles.h"
#include "../ai/PathfindingHelper.h"

USING_NS_CC;
using std::vector;



LevelHelper * LevelHelper:: create()
{
    auto helper = new LevelHelper;
    if (helper && helper->init()) {
        helper->autorelease();
        return helper;
    }
    
    CC_SAFE_DELETE(helper);
    return nullptr;
}


bool LevelHelper::init()
{    
    bool bCon = false;
    do {
        
        
        bCon = true;
        
    } while (false);
    
    return bCon;
}


LevelHelper::LevelHelper()
{
    
}

LevelHelper::~LevelHelper()
{
    
}


vector<Point> getMovingRange(Roles *selected)
{
    
}





