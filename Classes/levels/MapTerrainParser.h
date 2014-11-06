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
#include <unordered_map>

class LayerTerrainInfo : public cocos2d::Ref
{
public:
    
    class TileTerrain : public cocos2d::Ref
    {
    public:
        int _id;
        cocos2d::Value _value;
        
        unsigned terrainType;
        
        static TileTerrain* create(int id, cocos2d::Value value)
        {
            TileTerrain *ret = new TileTerrain(id, value);
            ret->autorelease();
            return ret;
        }
        
    protected:
        TileTerrain(int id, cocos2d::Value value): _id(id), _value(value) {};
    };
    
public:
    CREATE_FUNC(LayerTerrainInfo);
    
    /*
     *  tileSetName same as tile set which the terrain information belonged to.
     */
    CC_SYNTHESIZE_PASS_BY_REF(std::string, _tileSetName, Name);
    
    CC_SYNTHESIZE_PASS_BY_REF(cocos2d::ValueVector, _terrainTypes, TerrainTypes);
    
    CC_SYNTHESIZE_PASS_BY_REF(cocos2d::Vector<TileTerrain*>, _tileTerrainInfo, TileTerrainInfo);
    
protected:
    bool init(){ return true;}
    
};


class MapTerrainParser : public cocos2d::Ref, public cocos2d::SAXDelegator
{
public:
    /** creates a TMX Format with a tmx file */
    static MapTerrainParser * create(const std::string& tmxFile);
    
public:
    // implement pure virtual methods of SAXDelegator
    void startElement(void *ctx, const char *name, const char **atts);
    void endElement(void *ctx, const char *name);
    void textHandler(void *ctx, const char *ch, int len);
    
protected:
    /** initializes a TMX format with a  tmx file */
    bool initWithFile(const std::string& tmxFile);
    
    /** initializes parsing of an XML file, either a tmx (Map) file or tsx (Tileset) file */
    bool parseXMLFile(const std::string& xmlFilename);
    
    
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(cocos2d::Vector<LayerTerrainInfo *>, _layerTerrainInfo, TerrainInfo);
    
private:
    
    MapTerrainParser() : _terraininfo(nullptr)  {}
   
    
    LayerTerrainInfo *_terraininfo;
    cocos2d::ValueVector _terraintypes;
    cocos2d::Vector<LayerTerrainInfo::TileTerrain*> _tileTerrainInfo;
};




#endif /* defined(__SanGuoYingJie__MapTerrainParser__) */
