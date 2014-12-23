//
//  TerrainInfo.cpp
//  SanGuoYingJie
//
//  Created by Steven.Xc.Tian.
//
//

#include "TerrainInfo.h"
#include <algorithm>

USING_NS_CC;
using std::string;


TerrainInfo::Terrain TerrainInfo:: getTerrainType(string &name)
{
    // convert string to upper case.
    std::transform(name.begin(), name.end(), name.begin(), toupper);
    
    if (name == "PLAIN")
    {
        return TerrainInfo::Terrain::PLAIN;
    }
    else if (name == "GRASSLAND")
    {
        return TerrainInfo::Terrain::GRASSLAND;
    }
    else if (name == "FOREST")
    {
        return TerrainInfo::Terrain::FOREST;
    }
    else if (name == "MOUNTAIN")
    {
        return TerrainInfo::Terrain::MOUNTAIN;
    }
    else if (name == "BUILDING")
    {
        return TerrainInfo::Terrain::BUILDING;
    }
    else if (name == "WALL")
    {
        return TerrainInfo::Terrain::WALL;
    }
    else if (name == "WATER")
    {
        return TerrainInfo::Terrain::WATER;
    }
    else if (name == "CLIFF")
    {
        return TerrainInfo::Terrain::CLIFF;
    }
    else
    {
        CCLOGERROR("unsupport terrain !");
    }
    
    // others return UNKNOWN instead.
    return TerrainInfo::Terrain::UNKNOWN;
}

int TerrainInfo:: getTerrainCost(TerrainInfo::Terrain &terrain)
{
    switch (terrain) {
        case Terrain::PLAIN:
            return 1;
            
        case Terrain::GRASSLAND:
            return 1;
            
        case Terrain::FOREST:
            return 2;
            
        case Terrain::MOUNTAIN:
            return 2;
            
        case Terrain::BUILDING:
            return 2;
            
        default:
            // it means this terrain is impassable.
            return 100;
    }
}


