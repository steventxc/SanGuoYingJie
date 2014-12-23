//
//  TerrainInfo.h
//  SanGuoYingJie
//
//  Created by Steven.Xc.Tian.
//
//

#ifndef __SanGuoYingJie__TerrainInfo__
#define __SanGuoYingJie__TerrainInfo__

#include "cocos2d.h"

class TerrainInfo
{
public:
    enum class Terrain
    {
        UNKNOWN         = -1,
        PLAIN           = 1,
        GRASSLAND       = 1<<1,
        FOREST          = 1<<2,
        MOUNTAIN        = 1<<3,
        BUILDING        = 1<<4,
        // below terrains are impassable.
        WALL            = 1<<5,
        WATER           = 1<<6,
        CLIFF           = 1<<7,
    };
    
    static Terrain getTerrainType(std::string &name);
    
    static int getTerrainCost(Terrain &terrain);
    
    
    inline static bool isObstacle(Terrain terrain)
    {
        return ( static_cast<int>(terrain) >= static_cast<int>(Terrain::WALL) );
    }
    
private:
    TerrainInfo(){}
};

#endif /* defined(__SanGuoYingJie__TerrainInfo__) */
