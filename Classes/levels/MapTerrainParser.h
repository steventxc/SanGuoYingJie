//
//  MapTerrainParser.h
//  SanGuoYingJie
//
//  Created by Steven.Xc.Tian.
//
//

#ifndef __SanGuoYingJie__MapTerrainParser__
#define __SanGuoYingJie__MapTerrainParser__

#include "cocos2d.h"

class TileTerrain;

class MapTerrainParser : public cocos2d::Ref, public cocos2d::SAXDelegator {
public:
    /** creates a TMX Format with a tmx file */
    static MapTerrainParser * create(const std::string& tmxFile);
    
    /** initializes a TMX format with a  tmx file */
    bool initWithFile(const std::string& tmxFile);
    
    /** initializes parsing of an XML file, either a tmx (Map) file or tsx (Tileset) file */
    bool parseXMLFile(const std::string& xmlFilename);
    
public:
    // implement pure virtual methods of SAXDelegator
    void startElement(void *ctx, const char *name, const char **atts);
    void endElement(void *ctx, const char *name);
    void textHandler(void *ctx, const char *ch, int len);
    
protected:
    cocos2d::ValueVector terrainTypes;
    cocos2d::Vector<TileTerrain*> tileTerrainInfo;
};


class TileTerrain : public cocos2d::Ref
{
public:
    int id;
    cocos2d::Value value;
    
    CREATE_FUNC(TileTerrain);
    
    bool init()
    {
        id = -1;
        value = cocos2d::Value::Null;
        return true;
    }
};

#endif /* defined(__SanGuoYingJie__MapTerrainParser__) */
