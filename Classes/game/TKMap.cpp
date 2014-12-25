//
//  TKMap.cpp
//  SanGuoYingJie
//
//  Created by Steven.Xc.Tian.
//
//

#include "TKMap.h"


USING_NS_CC;
using std::string;


TKMap * TKMap::create(const string& tmxFile)
{
    TKMap *ret = new TKMap();
    if (ret->initData(tmxFile))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool TKMap:: initData(const string& tmxFile)
{
    if (! initWithTMXFile(tmxFile)) {
        return false;
    }
    
    
    return true;
}

bool TKMap:: isValidTileCoord(const Point &tileCoord)
{
    if (tileCoord.x < 0 || tileCoord.y < 0 ||
        tileCoord.x >= _mapSize.width || tileCoord.y >= _mapSize.height)
    {
        return false;
    }
    else
    {
        return true;
    }
}

Point TKMap:: getTileCoordByPosition(const Point &position)
{
    float x = floorf(position.x / _tileSize.width);
    float y = floorf(((_mapSize.height * _tileSize.height) - position.y) / _tileSize.height);
    
    return Point(x, y);
}

Point TKMap:: getPositionByTileCoord(const Point &tileCoord)
{
    CCASSERT(isValidTileCoord(tileCoord), "invalid tile coordinate.");
    
    float x = (tileCoord.x * _tileSize.width) + (_tileSize.width / 2);
    float y = (_mapSize.height * _tileSize.height) - (tileCoord.y * _tileSize.height)
    - (_tileSize.height / 2);
    
    return Point(x, y);
}


TerrainInfo::Terrain TKMap:: getTileTerrain(const cocos2d::Point& tileCoord)
{
    int gid = this->getLayer("terrain")->getTileGIDAt(tileCoord);
    auto perp = this->getPropertiesForGID(gid);
    
    if (!perp.isNull())
    {
        auto terrain = perp.asValueMap();
        
        auto iter = terrain.find("terrain");
        if (iter != terrain.end())
        {
            string tername(iter->second.asString());
            CCLOG("terrain: %s", tername.c_str());
            return TerrainInfo::getTerrainType(tername);
        }
    }
    
    return TerrainInfo::Terrain::UNKNOWN;
}


bool TKMap:: onTouchBegan(Touch* touch, Event* event)
{
    return false;
}

void TKMap:: onTouchMoved(Touch* touch, Event* event)
{
    
}

void TKMap:: onTouchEnded(Touch* touch, Event* event)
{
     
}




