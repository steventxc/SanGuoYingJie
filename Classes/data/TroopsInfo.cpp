//
//  TroopsInfo.cpp
//  SanGuoYingJie
//
//  Created by Steven.Xc.Tian.
//
//

#include "TroopsInfo.h"
#include "MapTerrain.h"



unsigned TroopsInfo:: getTerrainsWithType(TroopsType type)
{
    switch (type) {
        case TroopsType::INFANTRY :
            // 0x00011111;
            return MapTerrain::Terrain::PLAIN |  MapTerrain::Terrain::GRASSLAND
            | MapTerrain::Terrain::MOUNTAINLAND | MapTerrain::Terrain::BUILDING
            | MapTerrain::Terrain::FOREST;
            
        case TroopsType::CAVALRY :
            // 0x00011011
            return MapTerrain::Terrain::PLAIN |  MapTerrain::Terrain::GRASSLAND
            | MapTerrain::Terrain::MOUNTAINLAND | MapTerrain::Terrain::BUILDING;
            
        case TroopsType::ARCHER :
            // 0x00011111;
            return MapTerrain::Terrain::PLAIN |  MapTerrain::Terrain::GRASSLAND
            | MapTerrain::Terrain::MOUNTAINLAND | MapTerrain::Terrain::BUILDING
            | MapTerrain::Terrain::FOREST;
            
        default:
            break;
    }
}