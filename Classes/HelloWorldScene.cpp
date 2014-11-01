#include "HelloWorldScene.h"
#include "Roles.h"

USING_NS_CC;
using std::string;


Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("move.plist", "move.pvr.ccz");
    
    auto map = cocos2d::experimental::TMXTiledMap::create("level01.tmx");
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
    
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
