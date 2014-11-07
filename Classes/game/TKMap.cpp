//
//  TKMap.cpp
//  SanGuoYingJie
//
//  Created by Steven.Xc.Tian.
//
//

#include "TKMap.h"
#include "../data/MapTerrain.h"

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
    
    auto terrainParser = MapTerrainParser::create(tmxFile);
    _mapTerrainInfo = terrainParser->getTerrainInfo();
    
    
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
    int x = floorf(position.x / _tileSize.width);
    int y = floorf(((_mapSize.height * _tileSize.height) - position.y) / _tileSize.height);
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

int TKMap:: getTileGID(const Point& tileCoord, experimental::TMXLayer *layer/* = nullptr */)
{
    CCASSERT(isValidTileCoord(tileCoord), "invalid tile coordinate.");
    
    if (nullptr == layer) {
        layer = this->getLayer("background");
    }
    
    return layer->getTileGIDAt(tileCoord);
}


unsigned TKMap:: getTileTerrain(int tileGID, experimental::TMXLayer *layer/* = nullptr */)
{
    CCASSERT(tileGID >= 0, "tile id can not less than 0!");
    
    if (nullptr == layer) {
        layer = this->getLayer("background");
    }
    
    // convert the tile global id to local layer tile id.
    const int tileID = tileGID - layer->getTileSet()->_firstGid;
    const string tilesetName = layer->getTileSet()->_name;
    
    for (decltype(_mapTerrainInfo.begin()) iter = _mapTerrainInfo.begin();
         iter != _mapTerrainInfo.end(); ++iter)
    {
        if ((*iter)->getName() == tilesetName) {
            
            auto tiles = (*iter)->getTileTerrainInfo();
            
            int terraintypeid = -1;
            
            decltype(tiles.find(nullptr)) tile_it;
            for(tile_it = tiles.begin(); tile_it != tiles.end(); ++tile_it)
            {
                if (tileID == (*tile_it)->_id) {
                    CCLOG("key: %d, value: %s <--> %d", (*tile_it)->_id, (*tile_it)->_value.asString().c_str(), (*tile_it)->_value.asInt());
                    
                    terraintypeid = (*tile_it)->_value.asInt();
                    break;
                }
            }
            
            // find the tile terrain info.
            if (tile_it != tiles.end()) {
                auto types = (*iter)->getTerrainTypes();
                
                string terrainName = types.at(terraintypeid).asString();
                CCLOG("terrain type name: %s", terrainName.c_str());
                
                return MapTerrain::getTerrainType(terrainName);
            }
            
            break;
        }
    }
    
    return MapTerrain::Terrain::OBSTACLE;
}

bool TKMap:: isObstacle(const cocos2d::Point &tileCoord)
{
    if (!isValidTileCoord(tileCoord))
        return false;
    
    const int gid = getTileGID(tileCoord);
    
    return (MapTerrain::Terrain::OBSTACLE == getTileTerrain(gid));
}



