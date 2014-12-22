//
//  LevelScene.h
//  SanGuoYingJie
//
//  Created by Steven.Xc.Tian.
//
//

#ifndef __SanGuoYingJie__LevelScene__
#define __SanGuoYingJie__LevelScene__

#include "cocos2d.h"
#include "../data/TerrainInfo.h"

class TKMap;

class LevelScene : public cocos2d::Layer
{
    TKMap *_mTKMap; //
    
    std::vector<cocos2d::Point> _solution;
    
    cocos2d::experimental::TMXLayer *_terrainLayer;
    
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    CREATE_FUNC(LevelScene);
    
    virtual bool init() override;
    
private:
    
    void move(const cocos2d::Point &tileCoord);
    
    void justdoit();
    
public:
    void setMask(cocos2d::Sprite *role);
    
    TerrainInfo::Terrain getTerrain(const cocos2d::Point &tileCoord);
    
    bool isPassable(const cocos2d::Point &tileCoord);
};

#endif /* defined(__SanGuoYingJie__LevelScene__) */
