//
//  MapHelper.cpp
//  SanGuoYingJie
//
//  Created by Steven.Xc.Tian.
//
//

#include "MapHelper.h"
#include "MapTerrainParser.h"
#include "../data/MapTerrain.h"


USING_NS_CC;
using std::string;

// singleton stuff
static MapHelper *s_InstanceMapHelper = nullptr;

MapHelper * MapHelper:: getInstance()
{
    if (!s_InstanceMapHelper)
    {
        s_InstanceMapHelper = new (std::nothrow) MapHelper();
        CCASSERT(s_InstanceMapHelper, "FATAL: Not enough memory");
        s_InstanceMapHelper->init();
    }
    
    return s_InstanceMapHelper;
}

experimental::TMXTiledMap * MapHelper:: setupLevelMap(const string& file)
{
    do {
        auto map = experimental::TMXTiledMap::create(file);
        CC_BREAK_IF(!map);
        
        _mapSize = map->getMapSize();
        _mapTileSize = map->getTileSize();
        
        
        // get map terrain infomation
        auto terrainParser = MapTerrainParser::create(file);
       _mapTerrainInfo = terrainParser->getTerrainInfo();
        
    
        
        
        auto backgroundLayer = map->getLayer("background");
        CC_BREAK_IF(!backgroundLayer);
        
        
        
//        int gid = backgroundLayer->getTileGIDAt(Vec2(0,0));
//        Value properties = map->getPropertiesForGID(gid);
//        CCLOG("########## %s", properties.getDescription().c_str());
        
        
        
        auto buildingsLayer = map->getLayer("buildings");
        
        auto sp1 = buildingsLayer->getTileAt(Point(11, 8));
//        Point p = backgroundLayer->getPositionAt(Point(4,8));
//        sp1->setAnchorPoint(Point::ANCHOR_MIDDLE);
        sp1->setOpacity(90);
//        sp1->setPosition(p);
       
        
        
        string tileName = backgroundLayer->getTileSet()->_name;
        decltype(_mapTerrainInfo.begin()) iter;
        for (iter = _mapTerrainInfo.begin(); iter != _mapTerrainInfo.end(); ++iter) {
            if ((*iter)->getName() == tileName) {
                
                auto types = (*iter)->getTerrainTypes();
                for (decltype(types.begin()) it = types.begin(); it != types.end(); ++it) {
                    CCLOG("terrain type name: %s", it->asString().c_str());
                }
                
                auto tiles = (*iter)->getTileTerrainInfo();
                CCLOG("tile size : %ld \n", tiles.size());
                
                for(int i= 0; i < tiles.size(); i++)
                {
                    CCLOG("key: %d, value: %s <--> %d", tiles.at(i)->_id, tiles.at(i)->_value.asString().c_str(), tiles.at(i)->_value.asInt());
                }
            
                break;
            }
        }
        
        
        
        
        
        
        
        
        
        
        
        auto sp2 = backgroundLayer->getTileAt(Point(1, 1));
        sp2->setOpacity(100);
        
        auto listener = EventListenerTouchOneByOne::create();
        listener->onTouchBegan = [this](Touch *touch, Event *event){
            
            // 获取事件所绑定的 target
            auto target = static_cast<experimental::TMXLayer*>(event->getCurrentTarget());
            
            // 获取当前点击点所在相对按钮的位置坐标
            Point locationInNode = target->convertToNodeSpace(touch->getLocation());
//            Point locationInNode = touch->getLocation();
            Size s = target->getContentSize();
            Rect rect = Rect(0, 0, s.width, s.height);
            
            // 点击范围判断检测
            if (rect.containsPoint(locationInNode))
            {
                log("sprite began... x = %f, y = %f", locationInNode.x, locationInNode.y);
//                target->setOpacity(180);
                Point p =this->getTileCoordByPosition(locationInNode);
                CCLOG("tile Coord [%f, %f]", p.x, p.y);
                
                
                return true;
            }
            return false;
        };
        
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, backgroundLayer);
        
        return map;
        
    } while (false);
    
    return nullptr;
}

Point MapHelper:: getTileCoordByPosition(const Point &position)
{
    int x = floorf(position.x / _mapTileSize.width);
    int y = floorf(((_mapSize.height * _mapTileSize.height) - position.y) / _mapTileSize.height);
    return Point(x, y);
}

Point MapHelper:: getPositionByTileCoord(const Point &tileCoord)
{
    float x = (tileCoord.x * _mapTileSize.width) + (_mapTileSize.width / 2);
    float y = (_mapSize.height * _mapTileSize.height) - (tileCoord.y * _mapTileSize.height)
    - (_mapTileSize.height / 2);
    
    return Point(x, y);
}

unsigned MapHelper:: getTileTerrain(experimental::TMXLayer *layer)
{
    string tileName = layer->getTileSet()->_name;
    
    decltype(_mapTerrainInfo.begin()) iter;
    for (iter = _mapTerrainInfo.begin(); iter != _mapTerrainInfo.end(); ++iter) {
        if ((*iter)->getName() == tileName) {
            
            auto types = (*iter)->getTerrainTypes();
            for (decltype(types.begin()) it = types.begin(); it != types.end(); ++it) {
                CCLOG("terrain type name: %s", it->asString().c_str());
            }
            
            auto tiles = (*iter)->getTileTerrainInfo();
            CCLOG("tile size : %ld \n", tiles.size());
            
            for(int i= 0; i < tiles.size(); i++)
            {
                CCLOG("key: %d, value: %s <--> %d", tiles.at(i)->_id, tiles.at(i)->_value.asString().c_str(), tiles.at(i)->_value.asInt());
            }
            
            break;
        }
    }
}



MapHelper:: MapHelper() :
_mapSize(Size::ZERO), _mapTileSize(Size::ZERO)
{
    
}


