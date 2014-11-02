//
//  MapHelper.cpp
//  SanGuoYingJie
//
//  Created by Steven.Xc.Tian.
//
//

#include "MapHelper.h"


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
        
        
        auto backgroundLayer = map->getLayer("background");
        CC_BREAK_IF(!backgroundLayer);
        
        
        auto sp1 = backgroundLayer->getTileAt(Point(3, 8));
//        Point p = backgroundLayer->getPositionAt(Point(4,8));
//        sp1->setAnchorPoint(Point::ANCHOR_MIDDLE);
        sp1->setOpacity(90);
//        sp1->setPosition(p)
        ;
        
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
                Point p =this->tileCoordForPosition(locationInNode);
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

Point MapHelper:: tileCoordForPosition(Point position)
{
    int x = floorf(position.x / _mapTileSize.width);
    int y = floorf(((_mapSize.height * _mapTileSize.height) - position.y) / _mapTileSize.height);
    return Point(x, y);
}


bool MapHelper:: init()
{
    return true;
}

MapHelper:: MapHelper() :
_mapSize(Size::ZERO), _mapTileSize(Size::ZERO)
{
    
}


