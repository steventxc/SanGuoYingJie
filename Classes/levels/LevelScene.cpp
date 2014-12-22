//
//  LevelScene.cpp
//  SanGuoYingJie
//
//  Created by Steven.Xc.Tian.
//
//

#include "LevelScene.h"
#include "../game/TKMap.h"
#include "../game/Roles.h"
#include "../ai/PathfindingHelper.h"


USING_NS_CC;
using std::string;


Scene* LevelScene::createScene()
{
    auto scene = Scene::create();
    
    auto layer = LevelScene::create();
    if (nullptr != layer) {
        scene->addChild(layer);
    }
    
    return scene;
}

bool LevelScene:: init()
{
    if (! Layer::init())
        return false;
    
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    
    bool bCon = false;
    do {
        
        // init level helper. REFRESH
//        _levelHelper = LevelHelper::create(this, "level01.tmx");
        
        
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile("move.plist", "move.pvr.ccz");
        
        
        // init pathfinding helper
        PathfindingHelper::getInstance()->setup(this);
        
        // REFRESH
        _mTKMap = TKMap::create( "level01.tmx");
        
        
        
        
        this->addChild(_mTKMap, 2);
        _mTKMap->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        _mTKMap->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
        
        
        auto backgroundLayer = _mTKMap->getLayer("background");
        backgroundLayer->setVisible(false);
        
        
        auto masklayer = _mTKMap->getLayer("mask");
        masklayer->setVisible(false);
        
        _terrainLayer = _mTKMap->getLayer("terrain");
        CC_BREAK_IF(!_terrainLayer);
//        terrainLayer->setVisible(false);
        
        
        
        auto roles = _mTKMap->getObjectGroup("roles");
        auto objs = roles->getObjects();
        
        for (auto obj : objs) {
            auto o = obj.asValueMap();
            if (! o["name"].asString().empty()) {
                string roleName = o["name"].asString();
                CCLOG("role's name is %s", roleName.c_str());
                
                string still(roleName);
                still.append("_move3.png");
                CCLOG("%s",still.c_str());
                auto zhangfei = Roles::createWithSpriteFrameName(still);
                zhangfei->setLevelScene(this);
                _mTKMap->addChild(zhangfei, 10);
                zhangfei->setName("zhangfei");
//                zhangfei->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
                Point pt(o["x"].asFloat()+zhangfei->getContentSize().width / 2,
                         o["y"].asFloat()+zhangfei->getContentSize().height / 2);
                zhangfei->setPosition(pt);
                
                
                // animation
                roleName.append("_move%d.png");
                auto animation = Animation::create();
                for (int i = 1; i<3; i++) {
                    char szName[100] = {0};
                    sprintf(szName, roleName.c_str(), i);
                    animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(szName));
                }
                animation->setDelayPerUnit(0.3f);
                
                auto action = Animate::create(animation);
                zhangfei->runAction(RepeatForever::create(action));
            }
        }
        
        
        auto _listener = EventListenerTouchOneByOne::create();
        _listener->setSwallowTouches(true);
        _listener->onTouchBegan = [this](Touch *touch, Event *event){
            
            auto target = static_cast<TKMap*>(event->getCurrentTarget());
            
            Point locationInNode = target->convertToNodeSpace(touch->getLocation());
            Size s = target->getContentSize();
            Rect rect = Rect(0, 0, s.width, s.height);
            
            if (rect.containsPoint(locationInNode))
            {
//                this->setMask();
                this->move(locationInNode);
            
                return true;
            }
            
            return false;
        };
        
        _eventDispatcher->addEventListenerWithSceneGraphPriority(_listener, _mTKMap);
        
        bCon = true;
    } while (false);
    
    return bCon;
}

void LevelScene::move(const cocos2d::Point &goal)
{
    Point end = _mTKMap->getTileCoordByPosition(goal);
//    if (_mTKMap->isObstacle(end)) {
//        CCLOG("## this tile is OBSTACLE!");
//        return;
//    }
    
    auto role = dynamic_cast<Roles*>(_mTKMap->getChildByName("zhangfei"));
    Point start = _mTKMap->getTileCoordByPosition(role->getPosition());
    
    if (start == end) {
        CCLOG("you have already there!");
        return;
    }
    
    /*
    CCLOG("start point tile coord [%f, %f]", start.x, start.y);
    CCLOG("end point tile coord [%f, %f]", end.x, end.y);
    
    _solution = PathfindingHelper::getInstance()->startAStarSearch(start, end);
    
    justdoit();
    */
    
    _mTKMap->getTileTerrain(end);
    
//    auto perp =  _mTKMap->getPropertiesForGID(_terrainLayer->getTileGIDAt(end));
//    
//    if (!perp.isNull()) {
//        auto terrain = perp.asValueMap();
//        
//        auto iter = terrain.find("terrain");
//        if (iter != terrain.end()) {
//            CCLOG("terrain: %s", iter->second.asString().c_str());
//            
//        }
//    }
    
}

void LevelScene::justdoit()
{
    if (!_solution.empty()) {
        Point pot = _solution.front();
        
        _solution.erase(_solution.begin());
        
        pot = _mTKMap->getPositionByTileCoord(pot);
        
        auto role = _mTKMap->getChildByName("zhangfei");
        
        auto move = MoveTo::create(0.1f, pot);
        auto callback = CallFunc::create(CC_CALLBACK_0(LevelScene::justdoit, this));
        auto seq = Sequence::create(move, callback, NULL);
        role->runAction(seq);
    }
}

void LevelScene:: setMask(Sprite* role)
{
    Point pot = _mTKMap->getTileCoordByPosition(role->getPosition());
    
    auto tiles = PathfindingHelper::getInstance()->startFloodFill(pot, 5);
    
    auto masklayer = _mTKMap->getLayer("mask");
    masklayer->setVisible(true);
    
    for (vector<Point>::iterator itr = tiles.begin(); itr != tiles.end(); ++itr)
    {
        auto tile = masklayer->getTileAt( (*itr) );
        tile->setVisible(false);
    }
    
    
    
    
//    if (masklayer->isVisible()) {
//            masklayer->setVisible(false);
//        masklayer->getTileAt(Point(1,1))->setVisible(true);
//    }
//    else
//    {
//            masklayer->setVisible(true);
//        masklayer->getTileAt(Point(1,1))->setVisible(false);
//    }
    
    

}


TerrainInfo::Terrain LevelScene:: getTerrain(const Point &tileCoord)
{
    return _mTKMap->getTileTerrain(tileCoord);
}

bool LevelScene:: isPassable(const cocos2d::Point &tileCoord)
{
    return TerrainInfo::isObstacle(_mTKMap->getTileTerrain(tileCoord));
}




