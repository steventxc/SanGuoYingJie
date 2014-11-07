//
//  MapTerrain.cpp
//  SanGuoYingJie
//
//  Created by Steven.Xc.Tian.
//
//

#include "MapTerrain.h"
#include <algorithm>

USING_NS_CC;
using std::string;


int MapTerrain:: getTerrainType(string &name)
{
    // convert string to upper case.
    std::transform(name.begin(), name.end(), name.begin(), toupper);
    
    if (name == "OBSTACLE") {
        return OBSTACLE;
    } else if (name == "PLAIN") {
        return PLAIN;
    } else if (name == "GRASSLAND") {
        return GRASSLAND;
    } else if (name == "FOREST") {
        return FOREST;
    } else if (name == "MOUNTAINLAND") {
        return MOUNTAINLAND;
    } else if (name == "BUILDING") {
        return BUILDING;
    } else {
        CCASSERT(false, " unsupport terrain !");
    }
    
    // others return OBSTACLE instead.
    return OBSTACLE;
}