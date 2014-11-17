//
//  MapTerrain.h
//  SanGuoYingJie
//
//  Created by Steven.Xc.Tian.
//
//

#ifndef __SanGuoYingJie__MapTerrain__
#define __SanGuoYingJie__MapTerrain__

#include "cocos2d.h"

class MapTerrain
{
public:
    static const int TERRAIN_MASK = 0xffffffff;
    
    enum Terrain {
        OBSTACLE        = 0x10000000,
        PLAIN           = 0x00000001,
        GRASSLAND       = 0x00000010,
        FOREST          = 0x00000100,
        MOUNTAINLAND    = 0x00001000,
        BUILDING        = 0x00010000,
        // below terrains are impassable.
        WALL = OBSTACLE,
        WATER = OBSTACLE,
        CLIFF = OBSTACLE,
    };
    
    static int getTerrainType(std::string &name);
    
    inline static int getTerrainCost(unsigned terrain)
    {
        switch (terrain) {
            case PLAIN:
                return 1;
                
            case GRASSLAND:
                return 1;
                
            case FOREST:
                return 1;
                
            case MOUNTAINLAND:
                return 1;
                
            case BUILDING:
                return 1;

            default:
                // it means this terrain is impassable.
                return INT_MIN;
        }
    }
    
private:
    MapTerrain(){}
};

#endif /* defined(__SanGuoYingJie__MapTerrain__) */
