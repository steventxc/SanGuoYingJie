//
//  TKMap.h
//  SanGuoYingJie
//
//  Created by Steven.Xc.Tian.
//
//

#ifndef __SanGuoYingJie__TKMap__
#define __SanGuoYingJie__TKMap__

#include "cocos2d.h"
#include "../data/TerrainInfo.h"


class TKMap : public cocos2d::experimental::TMXTiledMap
{
    
protected:
    
    bool initData(const std::string& tmxFile);
    
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    
public:
    static TKMap * create(const std::string& tmxFile);
    
    /**
     *  Converts a node (local) space point to tile coordinates. The result is in Points.
     */
    cocos2d::Point getTileCoordByPosition(const cocos2d::Point &position);
    
    /**
     * converts a tile coordinate to map space point.
     */
    cocos2d::Point getPositionByTileCoord(const cocos2d::Point &tileCoord);
    
    /**
     * check if this node in the map scope.
     */
    bool isValidTileCoord(const cocos2d::Point &tileCoord);
    
    /**
     *  get terrain info at specific coordinate.
     *  return value see TerrainInfo::Terrain class.
     */
    TerrainInfo::Terrain getTileTerrain(const cocos2d::Point& tileCoord);
    
};

#endif /* defined(__SanGuoYingJie__TKMap__) */
