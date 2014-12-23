//
//  TroopsInfo.cpp
//  SanGuoYingJie
//
//  Created by Steven.Xc.Tian.
//
//

#include "TroopsInfo.h"
#include "TerrainInfo.h"



unsigned TroopsInfo:: getTerrainsWithType(TroopsType type)
{
    switch (type) {
        case TroopsType::INFANTRY :
            // 00011111;
            return (
                    static_cast<int>(TerrainInfo::Terrain::PLAIN)  |
                    static_cast<int>(TerrainInfo::Terrain::GRASSLAND) |
                    static_cast<int>(TerrainInfo::Terrain::MOUNTAIN) |
                    static_cast<int>(TerrainInfo::Terrain::BUILDING) |
                    static_cast<int>(TerrainInfo::Terrain::FOREST)
                    );
            
        case TroopsType::CAVALRY :
            // 00011011
            return (
                    static_cast<int>(TerrainInfo::Terrain::PLAIN) |
                    static_cast<int>(TerrainInfo::Terrain::GRASSLAND) |
                    static_cast<int>(TerrainInfo::Terrain::MOUNTAIN) |
                    static_cast<int>(TerrainInfo::Terrain::BUILDING)
                    );
            
        case TroopsType::ARCHER :
            // 00011111;
            return (
                    static_cast<int>(TerrainInfo::Terrain::PLAIN) |
                    static_cast<int>(TerrainInfo::Terrain::GRASSLAND) |
                    static_cast<int>(TerrainInfo::Terrain::MOUNTAIN) |
                    static_cast<int>(TerrainInfo::Terrain::BUILDING) |
                    static_cast<int>(TerrainInfo::Terrain::FOREST)
                    );
            
        default:
            break;
    }
}