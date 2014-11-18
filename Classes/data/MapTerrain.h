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
    enum Terrain {
        OBSTACLE        = 1,
        PLAIN           = 1<<1,
        GRASSLAND       = 1<<2,
        FOREST          = 1<<3,
        MOUNTAINLAND    = 1<<4,
        BUILDING        = 1<<5,
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
                return 1;
        }
    }
    
private:
    MapTerrain(){}
};

#endif /* defined(__SanGuoYingJie__MapTerrain__) */
