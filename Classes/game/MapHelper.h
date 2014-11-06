//
//  MapHelper.h
//  SanGuoYingJie
//
//  Created by Steven.Xc.Tian.
//
//

#ifndef __SanGuoYingJie__MapHelper__
#define __SanGuoYingJie__MapHelper__

#include "cocos2d.h"

class LayerTerrainInfo;

class MapHelper : public cocos2d::Node {
    friend class LevelScene;
    
public:
    static MapHelper * getInstance();
    
    
    
    cocos2d::experimental::TMXTiledMap * setupLevelMap(const std::string& file);
    
    /**
     *  Converts a node (local) space point to tile coordinates. The result is in Points.
     */
    cocos2d::Point getTileCoordByPosition(const cocos2d::Point &position);
    
    /**
     * converts a tile coordinate to map space point.
     */
    cocos2d::Point getPositionByTileCoord(const cocos2d::Point &tileCoord);
    
    unsigned getTileTerrain(cocos2d::experimental::TMXLayer *layer);
    
protected:
    MapHelper();
    
    bool init() { return true; };
    
private:
    cocos2d::Size _mapSize, _mapTileSize;
    
    cocos2d::Vector<LayerTerrainInfo *> _mapTerrainInfo; // map terrain info, help us to get path.
};

#endif /* defined(__SanGuoYingJie__MapHelper__) */