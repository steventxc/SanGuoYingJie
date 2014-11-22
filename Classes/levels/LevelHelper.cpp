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
#include "../game/TKMap.h"
#include "../ai/PathfindingHelper.h"

USING_NS_CC;
using std::vector;



LevelHelper * LevelHelper:: create(LevelScene *scene, const std::string& tmxFile)
{
    auto helper = new (std::nothrow) LevelHelper(scene);
    if (helper && helper->init(tmxFile)) {
        helper->autorelease();
        return helper;
    }
    
    CC_SAFE_DELETE(helper);
    return nullptr;
}


bool LevelHelper::init(const std::string& tmxFile)
{    
    bool bCon = false;
    do {
        
        // REFRESH
        _mTKMap = TKMap::create(tmxFile);
        CC_BREAK_IF(! _mTKMap);
        
        
        bCon = true;
        
    } while (false);
    
    return bCon;
}


LevelHelper::LevelHelper(LevelScene *scene)
{
    _mLevelScene = scene;
}

LevelHelper::~LevelHelper()
{
    
}


vector<Point> getMovingRange(Roles *selected)
{
    
}





