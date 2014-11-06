//
//  MapTerrain.h
//  SanGuoYingJie
//
//  Created by Steven.Xc.Tian.
//
//

#ifndef __SanGuoYingJie__MapTerrain__
#define __SanGuoYingJie__MapTerrain__

#include <iostream>

class MapTerrain
{
public:
    
    enum Terrain {
        OBSTACLE,
        PLAIN,
        GRASSLAND,
        FOREST,
        MOUNTAINLAND,
        BUILDING,
        // below terrains are impassable.
        WALL = OBSTACLE,
        WATER = OBSTACLE,
        CLIFF = OBSTACLE,
    };
    
    inline static int getTerrainCost(Terrain terrain)
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
    
};

#endif /* defined(__SanGuoYingJie__MapTerrain__) */
