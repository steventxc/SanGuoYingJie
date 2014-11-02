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

class MapHelper : public cocos2d::Node {
    friend class LevelScene;
    
public:
    static MapHelper * getInstance();
    
    bool init();
    
    cocos2d::experimental::TMXTiledMap * setupLevelMap(const std::string& file);
    
    cocos2d::Point tileCoordForPosition(cocos2d::Point position);
    
protected:
    MapHelper();
    
private:
    cocos2d::Size _mapSize, _mapTileSize;
    
};

#endif /* defined(__SanGuoYingJie__MapHelper__) */
