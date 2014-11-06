//
//  Roles.h
//  SanGuoYingJie
//
//  Created by Steven.Xc.Tian on 14-10-18.
//
//

#ifndef __SanGuoYingJie__Roles__
#define __SanGuoYingJie__Roles__

#include "cocos2d.h"

class Roles : public cocos2d::Sprite
{
public:
    /**
     * also see Sprite::create(const std::string& filename)
     */
    static Roles* create(const std::string& filename);
    
    /**
     * also see Sprite::createWithTexture(cocos2d::Texture2D *texture)
     */
    static Roles* createWithTexture(cocos2d::Texture2D *texture);
    
    /**
     * also see Sprite::createWithSpriteFrame(cocos2d::SpriteFrame *spriteFrame)
     */
    static Roles* createWithSpriteFrame(cocos2d::SpriteFrame *spriteFrame);
    
    /**
     * also see Sprite::createWithSpriteFrameName(const std::string& spriteFrameName)
     */
    static Roles* createWithSpriteFrameName(const std::string& spriteFrameName);
    
protected:
    Roles(){};
    
    /**
     * also see Sprite::initWithTexture(cocos2d::Texture2D *texture, const cocos2d::Rect& rect, bool rotated)
     */
    virtual bool initWithTexture(cocos2d::Texture2D *texture);
    
    /**
     * also see Sprite::initWithTexture(cocos2d::Texture2D *texture, const cocos2d::Rect& rect, bool rotated)
     */
    virtual bool initWithTexture(cocos2d::Texture2D *texture, const cocos2d::Rect& rect, bool rotated);
};

#endif /* defined(__SanGuoYingJie__Roles__) */
