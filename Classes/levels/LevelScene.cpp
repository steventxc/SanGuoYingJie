//
//  LevelScene.cpp
//  SanGuoYingJie
//
//  Created by Steven.Xc.Tian.
//
//

#include "LevelScene.h"
#include "../game/MapHelper.h"
#include "../game/Roles.h"
#include "../game/MapTerrainParser.h"


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
        
        
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile("move.plist", "move.pvr.ccz");
        
        //    auto map = cocos2d::experimental::TMXTiledMap::create("level01.tmx");
        auto helper = MapHelper::create("");
        auto map = helper->setupLevelMap("level01.tmx");
        
        MapTerrainParser::create("level01.tmx");
        
        this->addChild(map, 2);
        map->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        map->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
        
        auto roles = map->getObjectGroup("roles");
        auto objs = roles->getObjects();
        for (auto obj : objs) {
            auto o = obj.asValueMap();
            if (! o["name"].asString().empty()) {
                string roleName = o["name"].asString();
                CCLOG("role's name is %s", roleName.c_str());
                
                string still(roleName);
                still.append("_move3.png");
                CCLOG("%s",still.c_str());
                auto chara = Roles::createWithSpriteFrameName(still);
                map->addChild(chara, 1);
                chara->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
                chara->setPosition(o["x"].asFloat(),o["y"].asFloat());
                
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
                chara->runAction(RepeatForever::create(action));
            }
        }
        
        
        bCon = true;
    } while (false);
    
    return bCon;
}