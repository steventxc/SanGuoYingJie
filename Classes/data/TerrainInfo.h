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
        PLAIN           = 1<<1,
        GRASSLAND       = 1<<2,
        FOREST          = 1<<3,
        MOUNTAINLAND    = 1<<4,
        BUILDING        = 1<<5,
        // below terrains are impassable.
        WALL            = 1<<6,
        WATER           = 1<<7,
        CLIFF           = 1<<8,
    };
    
    static Terrain getTerrainType(std::string &name);
    
    static int getTerrainCost(Terrain &terrain);
    
    
    inline static bool isObstacle(Terrain terrain)
    {
        return ( terrain >= Terrain::WALL );
    }
    
private:
    TerrainInfo(){}
};

#endif /* defined(__SanGuoYingJie__MapTerrain__) */
