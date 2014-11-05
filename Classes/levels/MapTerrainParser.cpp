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
//    TMXMapInfo *tmxMapInfo = this;
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
    
    if (elementName == "terraintypes") {
        
        // <terraintypes> tag start
        terrainTypes.clear();
        
    } else if (elementName == "terrain") {
        // get terrain types in order
        CCLOG("terrain type name: %s", attributeDict["name"].asString().c_str());
        terrainTypes.push_back(attributeDict["name"]);
        
    } else if (elementName == "tile") {
        
        for (decltype(attributeDict.begin())it = attributeDict.begin(); it!=attributeDict.end(); ++it) {
            
            CCLOG("key: %s, value: %s", it->first.c_str(), it->second.getDescription().c_str());
        }
        
//        if (tmxMapInfo->getParentElement() == TMXPropertyLayer)
//        {
//            TMXLayerInfo* layer = tmxMapInfo->getLayers().back();
//            Size layerSize = layer->_layerSize;
//            uint32_t gid = static_cast<uint32_t>(attributeDict["gid"].asInt());
//            int tilesAmount = layerSize.width*layerSize.height;
//            
//            if (_xmlTileIndex < tilesAmount)
//            {
//                layer->_tiles[_xmlTileIndex++] = gid;
//            }
//        }
//        else
//        {
//            TMXTilesetInfo* info = tmxMapInfo->getTilesets().back();
//            tmxMapInfo->setParentGID(info->_firstGid + attributeDict["id"].asInt());
//            tmxMapInfo->getTileProperties()[tmxMapInfo->getParentGID()] = Value(ValueMap());
//            tmxMapInfo->setParentElement(TMXPropertyTile);
//        }
        
    }
}


void MapTerrainParser:: endElement(void *ctx, const char *name)
{
    CC_UNUSED_PARAM(ctx);
    string elementName(name);
    
    if (elementName == "tile") {
        CCLOG("============================");
    }
}

void MapTerrainParser:: textHandler(void *ctx, const char *ch, int len)
{
    CC_UNUSED_PARAM(ctx);
//    TMXMapInfo *tmxMapInfo = this;
    string elementName(ch);
    
    CCLOG("********** %s", elementName.c_str());
    
//    if (tmxMapInfo->isStoringCharacters())
//    {
//        std::string currentString = tmxMapInfo->getCurrentString();
//        currentString += text;
//        tmxMapInfo->setCurrentString(currentString.c_str());
//    }

}

void split(std::string& s, std::string& delim,std::vector< std::string >* ret)
{
    size_t last = 0;
    size_t index=s.find_first_of(delim,last);
    while (index!=std::string::npos)
    {
        ret->push_back(s.substr(last,index-last));
        last=index+1;
        index=s.find_first_of(delim,last);
    }
    if (index-last>0)
    {
        ret->push_back(s.substr(last,index-last));
    }
}






