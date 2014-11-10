//
//  LevelHelper.h
//  SanGuoYingJie
//
//  Created by Steven.Xc.Tian.
//
//

#ifndef __SanGuoYingJie__LevelHelper__
#define __SanGuoYingJie__LevelHelper__

#include "cocos2d.h"

class Roles;

class LevelHelper : public cocos2d::Ref
{
public:
    
    static LevelHelper * create();
    
    
    std::vector<cocos2d::Point> getMovingRange(Roles *selected);
    
protected:
    LevelHelper();
    ~LevelHelper();
    
    bool init();
};

#endif /* defined(__SanGuoYingJie__LevelHelper__) */
