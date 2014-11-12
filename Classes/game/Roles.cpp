//
//  Roles.cpp
//  SanGuoYingJie
//
//  Created by Steven.Xc.Tian on 14-10-18.
//
//

#include "Roles.h"
#include "../levels/LevelScene.h"

USING_NS_CC;

Roles* Roles::create(const std::string& filename)
{
    Roles *sprite = new (std::nothrow) Roles();
    if (sprite && sprite->initWithFile(filename))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

Roles* Roles::createWithTexture(Texture2D *texture)
{
    Roles *sprite = new (std::nothrow) Roles();
    if (sprite && sprite->Sprite::initWithTexture(texture))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

Roles* Roles::createWithSpriteFrame(SpriteFrame *spriteFrame)
{
    Roles *sprite = new (std::nothrow) Roles();
    if (sprite && spriteFrame && sprite->initWithSpriteFrame(spriteFrame))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

Roles* Roles::createWithSpriteFrameName(const std::string& spriteFrameName)
{
    SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameName);
    
#if COCOS2D_DEBUG > 0
    char msg[256] = {0};
    sprintf(msg, "Invalid spriteFrameName: %s", spriteFrameName.c_str());
    CCASSERT(frame != nullptr, msg);
#endif
    
    return createWithSpriteFrame(frame);
}

//bool Roles::initWithTexture(Texture2D *texture)
//{
//    CCASSERT(texture != nullptr, "Invalid texture for sprite");
//    
//    Rect rect = Rect::ZERO;
//    rect.size = texture->getContentSize();
//    
//    return Sprite::initWithTexture(texture, rect);
//}

bool Roles::initWithTexture(Texture2D *texture, const Rect& rect, bool rotated)
{
    if (! Sprite::initWithTexture(texture, rect, rotated)) {
        return false;
    }
    
    // add touch listener
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [this](Touch *touch, Event *event) {
        
        auto target = static_cast<Roles*>(event->getCurrentTarget());
        
        Point locationInNode = target->convertToNodeSpace(touch->getLocation());
        Size s = target->getContentSize();
        Rect rect = Rect(0, 0, s.width, s.height);
        
        if (rect.containsPoint(locationInNode))
        {
            this->_isSelected = true;
    
            _levelScene->setMask(this);
            
            return true;
        }
    
        return false;
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}



