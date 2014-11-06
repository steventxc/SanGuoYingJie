//
//  MapTerrainParser.cpp
//  SanGuoYingJie
//
//  Created by Steven.Xc.Tian on 14/11/5.
//
//

#include "MapTerrainParser.h"

USING_NS_CC;
using std::string;


static void split(const std::string& s, const std::string& delim, std::vector< std::string >& ret)
{
    size_t last = 0;
    size_t index = s.find_first_of(delim,last);
    while (index!=std::string::npos)
    {
        ret.push_back(s.substr(last,index-last));
        last=index+1;
        index=s.find_first_of(delim,last);
    }
    if (index-last>0)
    {
        ret.push_back(s.substr(last,index-last));
    }
}


MapTerrainParser * MapTerrainParser:: create(const std::string& tmxFile)
{
    MapTerrainParser *ret = new MapTerrainParser();
    if(ret->initWithFile(tmxFile))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;

}

bool MapTerrainParser:: initWithFile(const std::string& tmxFile)
{
    return parseXMLFile(tmxFile);
}

bool MapTerrainParser:: parseXMLFile(const string &xmlFilename)
{
    SAXParser parser;
    
    if (false == parser.init("UTF-8") )
    {
        return false;
    }
    
    parser.setDelegator(this);
    
    return parser.parse(FileUtils::getInstance()->fullPathForFilename(xmlFilename).c_str());
}

void MapTerrainParser:: startElement(void *ctx, const char *name, const char **atts)
{
    CC_UNUSED_PARAM(ctx);
    
    string elementName(name);
    ValueMap attributeDict;
    if (atts && atts[0])
    {
        for(int i = 0; atts[i]; i += 2)
        {
            std::string key = (char*)atts[i];
            std::string value = (char*)atts[i+1];
            attributeDict.insert(std::make_pair(key, Value(value)));
        }
    }
    
    if (elementName == "map") {
        
        _layerTerrainInfo.clear();
        
    } else if (elementName == "tileset") {
        
        // create a new LayerTerrainInfo object.
        if (_terraininfo != nullptr)
            CC_SAFE_RELEASE_NULL(_terraininfo);
        
        
        _terraininfo = LayerTerrainInfo::create();
        _terraininfo->setName(attributeDict["name"].asString());
        
        
    } else if (elementName == "terraintypes") {
        
        // <terraintypes> tag start
        _terraintypes.clear();
        
    } else if (elementName == "terrain") {
        // get terrain types of current tile set in order
        _terraintypes.push_back(attributeDict["name"]);
        
    } else if (elementName == "tile") {
 
        std::vector<string> data;
        split(attributeDict["terrain"].asString(), ",", data);
        Value value;
        
        // entire tile have only one terrain type
        for (int i =0; i<data.size(); i++)
        {
            if (!data[i].empty()) {
                value = data[i];
                break;
            }
        }
        
        auto tileTerrain = LayerTerrainInfo::TileTerrain::create(attributeDict["id"].asInt(), value);
        //
        _tileTerrainInfo.pushBack(tileTerrain);
    }
}


void MapTerrainParser:: endElement(void *ctx, const char *name)
{
    CC_UNUSED_PARAM(ctx);
    string elementName(name);
    
    if (elementName == "tileset") {
        
        // add terrain info for every specified tile.
        _terraininfo->setTileTerrainInfo(_tileTerrainInfo);
        
        // add a layer terrain infomation to vector and release the temporary one for reuse.
        _layerTerrainInfo.pushBack(_terraininfo);
        CC_SAFE_RELEASE_NULL(_terraininfo);
        
    } else if (elementName == "terraintypes") {
        
        // end of </terraintypes>, set the terrain types info.
        if (nullptr != _terraininfo) {
            _terraininfo->setTerrainTypes(_terraintypes);
        }
        
        // prepare to add tiles.
        _tileTerrainInfo.clear();
        
    }

}

void MapTerrainParser:: textHandler(void *ctx, const char *ch, int len)
{
    CC_UNUSED_PARAM(ctx);
    string text(ch, len);
}






