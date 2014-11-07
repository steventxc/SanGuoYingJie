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
#include "MapTerrainParser.h"


class TKMap : public cocos2d::experimental::TMXTiledMap
{
    cocos2d::Vector<LayerTerrainInfo *> _mapTerrainInfo; // map terrain info, help us to get path.
    
protected:
    
    bool initData(const std::string& tmxFile);
    
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
     *
     */
    int getTileGID(const cocos2d::Point& tileCoord, cocos2d::experimental::TMXLayer *layer = nullptr);
    
    /**
     * check if this node in the map scope.
     */
    bool isValidTileCoord(const cocos2d::Point &tileCoord);
    
    /**
     *  check if this tile is obstacle. out of map is as obstacle also.
     */
    bool isObstacle(const cocos2d::Point &tileCoord);
    
    /**
     *  get terrain info of the tile which belonged to the layer.
     *  return value see MapTerrain::Terrain class.
     *  default layer's name is "background"
     */
    unsigned getTileTerrain(int tileGID, cocos2d::experimental::TMXLayer *layer = nullptr);
    
};

#endif /* defined(__SanGuoYingJie__TKMap__) */
